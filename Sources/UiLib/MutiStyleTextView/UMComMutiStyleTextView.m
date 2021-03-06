//
//  UMComMutiStyleTextView.m
//  UMCommunity
//
//  Created by umeng on 15-3-5.
//  Copyright (c) 2015年 Umeng. All rights reserved.
//

#import "UMComMutiStyleTextView.h"
#import "UMComTools.h"


CTFontRef CTFontCreateFromUIFont(UIFont *font)
{
    CTFontRef ctFont = CTFontCreateWithName((__bridge CFStringRef)font.fontName,
                                            font.pointSize,
                                            NULL);
    return ctFont;
}


@interface UMComMutiStyleTextView ()


@end

@implementation UMComMutiStyleTextView

- (id)init
{
    self = [super init];
    if (self) {
        [self createDefault];
    }
    return self;
}

- (void)dealloc
{
    if (_framesetterRef) {
        CFRelease((__bridge_retained  CTFramesetterRef)(_framesetterRef));
        _framesetterRef = NULL;
    }
}



- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self createDefault];
    }
    return self;
}

- (void)setMutiStyleTextViewProperty:(UMComMutiStyleTextView *)styleTextView
{
    self.attributedText = styleTextView.attributedText;
    self.framesetterRef = styleTextView.framesetterRef;
    self.runs = styleTextView.runs;
    [self setNeedsDisplay];
}



#pragma mark - CreateDefault

- (void)createDefault
{
    //public
    _text        = nil;
    _font        = [UIFont systemFontOfSize:13.0f];
    _textColor   = [UIColor blackColor];
    _runType = UMComMutiTextRunNoneType;//UMComMutiTextRunURLType | UMComMutiTextRunEmojiType;
    _lineSpace   = 2.0f;
//    self.heightOffset = 0.0f;
    _attributedText = nil;
    _pointOffset = CGPointZero;
    //private
    _runs        = [NSMutableArray array];
    _runRectDictionary = [NSMutableDictionary dictionary];
    _touchRun = nil;
    _checkWords = [NSMutableArray arrayWithCapacity:1];
    _framesetterRef = NULL;
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(tapInCerrentView:)];
    [self addGestureRecognizer:tap];
}



#pragma mark - Set
- (void)setText:(NSString *)text
{
    [self setNeedsDisplay];

    _text = text;
}


- (void)awakeFromNib
{
    [self createDefault];

}

#pragma mark - Draw Rect

- (void)drawRect:(CGRect)rect
{
    //绘图上下文
    CGContextRef contextRef = UIGraphicsGetCurrentContext();
    if (self.attributedText == nil || self.attributedText.length == 0 ){
        return;
    }

    CGRect viewRect = CGRectMake(self.pointOffset.x, -self.pointOffset.y, rect.size.width, rect.size.height);//
    //修正坐标系
    CGAffineTransform affineTransform = CGAffineTransformIdentity;
    affineTransform = CGAffineTransformMakeTranslation(0.0, viewRect.size.height);
    affineTransform = CGAffineTransformScale(affineTransform, 1.0, -1.0);
    CGContextConcatCTM(contextRef, affineTransform);
    
    //创建一个用来描画文字的路径，其区域为viewRect  CGPath
    CGMutablePathRef pathRef = CGPathCreateMutable();
    CGPathAddRect(pathRef, NULL, viewRect);

    CTFramesetterRef frameSetter = CFRetain((__bridge CTFramesetterRef)(self.framesetterRef));
    CTFrameRef frameRef = CTFramesetterCreateFrame(frameSetter, CFRangeMake(0, 0), pathRef, nil);
    //通过context在frame中描画文字内容
    CTFrameDraw(frameRef, contextRef);
    [self.runRectDictionary removeAllObjects];
    [self setRunsKeysToRunRectWithFrameRef:frameRef];
    CGPathRelease(pathRef);
    CFRelease(frameRef);
    CFRelease(frameSetter);
}

- (void)setRunsKeysToRunRectWithFrameRef:(CTFrameRef)frameRef
{
    CFArrayRef lines = CTFrameGetLines(frameRef);
    CGPoint lineOrigins[CFArrayGetCount(lines)];
    CTFrameGetLineOrigins(frameRef, CFRangeMake(0, 0), lineOrigins);
    
    for (int i = 0; i < CFArrayGetCount(lines); i++)
    {
        CTLineRef lineRef= CFArrayGetValueAtIndex(lines, i);
        CGFloat lineAscent;
        CGFloat lineDescent;
        CGFloat lineLeading;
        CGPoint lineOrigin = CGPointMake(lineOrigins[i].x, lineOrigins[i].y);//
        CTLineGetTypographicBounds(lineRef, &lineAscent, &lineDescent, &lineLeading);
        CFArrayRef runs = CTLineGetGlyphRuns(lineRef);
        
        for (int j = 0; j < CFArrayGetCount(runs); j++)
        {
            CTRunRef runRef = CFArrayGetValueAtIndex(runs, j);
            CGFloat runAscent;
            CGFloat runDescent;
            CGRect runRect;
            
            runRect.size.width = CTRunGetTypographicBounds(runRef, CFRangeMake(0,0), &runAscent, &runDescent, NULL);
            runRect = CGRectMake(lineOrigin.x + CTLineGetOffsetForStringIndex(lineRef, CTRunGetStringRange(runRef).location, NULL),
                                 lineOrigin.y,
                                 runRect.size.width,
                                 runAscent + runDescent);
            
            NSDictionary * attributes = (__bridge NSDictionary *)CTRunGetAttributes(runRef);
            UMComMutiTextRun *mutiTextRun = [attributes objectForKey:UMComMutiTextRunAttributedName];
            if (mutiTextRun.drawSelf)
            {
                CGFloat runAscent,runDescent;
                CGFloat runWidth  = CTRunGetTypographicBounds(runRef, CFRangeMake(0,0), &runAscent, &runDescent, NULL);
                CGFloat runHeight = (lineAscent + lineDescent );
                CGFloat runPointX = runRect.origin.x + lineOrigin.x;
                CGFloat runPointY = lineOrigin.y;
                
                CGRect runRectDraw = CGRectMake(runPointX, runPointY, runWidth, runHeight);
                
                [mutiTextRun drawRunWithRect:runRectDraw];
                
                [self.runRectDictionary setObject:mutiTextRun forKey:[NSValue valueWithCGRect:runRectDraw]];
            }
            else
            {
                if (mutiTextRun)
                {
                    [self.runRectDictionary setObject:mutiTextRun forKey:[NSValue valueWithCGRect:runRect]];
                }
            }
        }
    }
}


- (void)tapInCerrentView:(UITapGestureRecognizer *)tap
{
    CGPoint location = [tap locationInView:self];
    CGPoint runLocation = CGPointMake(location.x-self.pointOffset.x, self.frame.size.height - location.y+self.pointOffset.y+2);
    
    __weak UMComMutiStyleTextView *weakSelf = self;
    if (self.clickOnlinkText) {
        if (self.runRectDictionary.count > 0) {
            BOOL isInclude = NO;
            for (NSValue *key in [self.runRectDictionary allKeys]) {
                id object = [self.runRectDictionary objectForKey:key];                
                CGRect rect = [((NSValue *)key) CGRectValue];
                if(CGRectContainsPoint(rect, runLocation))
                {
                    isInclude = YES;
                    weakSelf.touchRun = (UMComMutiTextRun *)object;
                    if ([object isKindOfClass:[UMComMutiTextRunURL class]]) {
                        if (![[weakSelf.touchRun.text lowercaseString] hasPrefix:@"http"]) {
                            weakSelf.touchRun.text = [NSString stringWithFormat:@"http://%@",weakSelf.touchRun.text];
                        }
                    }
                    break;
                }
            }
            if (isInclude == YES) {
                weakSelf.clickOnlinkText(self,weakSelf.touchRun);
            }else{
                weakSelf.clickOnlinkText(self,nil);
            }
        }else{
            weakSelf.clickOnlinkText(self,nil);
        }

    }

}


#pragma mark -

+ (NSMutableAttributedString *)createAttributedStringWithText:(NSString *)text font:(UIFont *)font lineSpace:(CGFloat)lineSpace
{
    NSMutableAttributedString *attString = [[NSMutableAttributedString alloc] initWithString:text];
    //设置字体
    CTFontRef fontRef = CTFontCreateFromUIFont(font);//CTFontCreateWithName((__bridge CFStringRef)font.fontName, font.pointSize, NULL);
    [attString addAttribute:(NSString*)kCTFontAttributeName value:(__bridge id)fontRef range:NSMakeRange(0,attString.length)];
    CFRelease(fontRef);
    
    //添加换行模式
    CTParagraphStyleSetting lineBreakMode;
    CTLineBreakMode lineBreak = kCTLineBreakByWordWrapping;
    lineBreakMode.spec        = kCTParagraphStyleSpecifierLineBreakMode;
    lineBreakMode.value       = &lineBreak;
    lineBreakMode.valueSize   = sizeof(lineBreak);

    //行距
    CTParagraphStyleSetting lineSpaceStyle;
    lineSpaceStyle.spec = kCTParagraphStyleSpecifierLineSpacing;
    lineSpaceStyle.valueSize = sizeof(lineSpace);
    lineSpaceStyle.value =&lineSpace;
    
    CTParagraphStyleSetting settings[] = {lineSpaceStyle,lineBreakMode};
    CTParagraphStyleRef style = CTParagraphStyleCreate(settings, sizeof(settings)/sizeof(settings[0]));
    NSMutableDictionary *attributes = [NSMutableDictionary dictionaryWithObject:(__bridge id)style forKey:(id)kCTParagraphStyleAttributeName ];
    CFRelease(style);
    
    [attString addAttributes:attributes range:NSMakeRange(0, [attString length])];
    
    return attString;
}

+ (NSArray *)createTextRunsWithAttString:(NSMutableAttributedString *)attString
                                 runType:(UMComMutiTextRunTypeList)type
                                    font:(UIFont *)font
                              checkWords:(NSArray *)checkWords
{
    NSMutableArray *array = [[NSMutableArray alloc] init];
    UIColor *blueColor = [UMComTools colorWithHexString:FontColorBlue];
    if (type == UMComMutiTextRunFeedContentType || type == UMComMutiTextRunCommentType || type == UMComMutiTextRunLikeType || UMComMutiTextRunNoneType)
    {
        [array addObjectsFromArray:[UMComMutiTextRunURL runsWithAttributedString:attString font:font textColor:blueColor]];
        [array addObjectsFromArray:[UMComMutiTextRunTopic runsWithAttributedString:attString font:font textColor:blueColor checkWords:checkWords]];
        [array addObjectsFromArray:[UMComMutiTextRunClickUser runsWithAttributedString:attString font:font textColor:blueColor checkWords:checkWords]];
    }
    return  array;
}


- (NSArray *)runsWithattributString:(NSMutableAttributedString *)attribuString
                               Font:(UIFont *)font
                          lineSpace:(CGFloat )lineSpace
                              color:(UIColor *)color
                         checkWords:(NSArray *)checkWords
{
    return nil;
}

+ (UMComMutiStyleTextView *)rectDictionaryWithSize:(CGSize)size
                                              font:(UIFont *)font
                                         attString:(NSString *)string
                                         lineSpace:(CGFloat )lineSpace
                                           runType:(UMComMutiTextRunTypeList)runType
                                        checkWords:(NSMutableArray *)checkWords
{
    UMComMutiStyleTextView * styleTextView = [[UMComMutiStyleTextView alloc] init];
    styleTextView.runType = runType;
    styleTextView.checkWords = checkWords;
    [styleTextView rectDictionaryWithSize:size font:font attString:string lineSpace:lineSpace];
    return styleTextView;
}

- (void)rectDictionaryWithSize:(CGSize)size font:(UIFont *)font attString:(NSString *)string lineSpace:(CGFloat )lineSpace
{
    if (!string || string.length == 0) {
        return;
    }
    CGFloat shortestLineWith = 0;
    int lineCount = 0;
    NSMutableAttributedString *attString = [[self class] createAttributedStringWithText:string font:font lineSpace:lineSpace];
    NSDictionary *dic = [attString attributesAtIndex:0 effectiveRange:nil];
    CTParagraphStyleRef paragraphStyle = (__bridge CTParagraphStyleRef)[dic objectForKey:(id)kCTParagraphStyleAttributeName];
    CGFloat linespace = 0;
    
    CTParagraphStyleGetValueForSpecifier(paragraphStyle, kCTParagraphStyleSpecifierLineSpacing, sizeof(linespace), &linespace);
    
    CGFloat height = 0;
    CGFloat width = 0;
    CFIndex lineIndex = 0;
    
    CGMutablePathRef pathRef = CGPathCreateMutable();
    CGPathAddRect(pathRef, NULL, CGRectMake(0, 0, size.width, size.height));
    
    NSArray *runs = [[self class] createTextRunsWithAttString:attString runType:self.runType font:font checkWords:self.checkWords];
    self.runs = runs;
    
    CFAttributedStringRef attStringRef = (__bridge CFAttributedStringRef)attString;
    CTFramesetterRef setterRef = CTFramesetterCreateWithAttributedString(attStringRef);
    self.framesetterRef = (__bridge_transfer id)(CFRetain(setterRef));
    CTFrameRef frameRef = CTFramesetterCreateFrame(setterRef, CFRangeMake(0, 0), pathRef, nil);
    CFArrayRef lines = CTFrameGetLines(frameRef);
    
    lineIndex = CFArrayGetCount(lines);
    lineCount = (int)lineIndex;
    
    CTLineRef lineRef;
    if (lineIndex > 1)
    {
        for (int i = 0; i <lineIndex ; i++)
        {
            lineRef= CFArrayGetValueAtIndex(lines, i);
            if (i == lineIndex - 1) {
                CGRect rect = CTLineGetBoundsWithOptions(lineRef,kCTLineBoundsExcludeTypographicShifts);
                shortestLineWith = rect.size.width;
//                self.lineHeight = rect.size.height + lineSpace;
            }
            CGFloat lineAscent;
            CGFloat lineDescent;
            CGFloat lineLeading;
            CTLineGetTypographicBounds(lineRef, &lineAscent, &lineDescent, &lineLeading);
            
            if (i == lineIndex - 1)
            {
                height += (lineAscent + lineDescent +linespace);
            }
            else
            {
                height += (lineAscent + lineDescent + linespace);
            }
        }
        width = size.width;
    }
    else
    {
        lineRef= CFArrayGetValueAtIndex(lines, 0);
        CGRect rect = CTLineGetBoundsWithOptions(lineRef,kCTLineBoundsExcludeTypographicShifts);
        shortestLineWith = rect.size.width;
//        self.lineHeight = rect.size.height + linespace;
        width = rect.size.width;
        CGFloat lineAscent;
        CGFloat lineDescent;
        CGFloat lineLeading;
        CTLineGetTypographicBounds(lineRef, &lineAscent, &lineDescent, &lineLeading);
        
        height += (lineAscent + lineDescent + lineLeading + linespace);
        height = height;
    }
    
    self.totalHeight = height + lineSpace/2;
//    self.lastLineWidth = shortestLineWith;
//    self.lineCount = lineCount;
    self.attributedText = attString;
    CGPathRelease(pathRef);
    CFRelease(setterRef);
    CFRelease(frameRef);
}

@end

