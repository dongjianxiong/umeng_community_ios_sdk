//
//  UMComImageModel.h
//  UMCommunity
//
//  Created by umeng on 15/9/25.
//  Copyright (c) 2015年 Umeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UMComImageModel : NSObject

@property (nonatomic, copy) NSString *smallImageUrlString;//小图

@property (nonatomic, copy) NSString *midlleImageUrlString;//中图

@property (nonatomic, copy) NSString *largeImageUrlString;//大图

@property (nonatomic, copy) NSString *format;

+ (UMComImageModel *)comImageModelWithUserIconDict:(NSDictionary *)imageDict;

+ (UMComImageModel *)comImageModelWithTopipImageDict:(NSDictionary *)imageDict;

+ (UMComImageModel *)comImageModelWithFeedImageDict:(NSDictionary *)imageDict;

@end
