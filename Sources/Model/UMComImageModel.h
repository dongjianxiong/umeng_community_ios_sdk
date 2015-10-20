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

//将用户icon图片集转化成UMComImageModel类型
+ (UMComImageModel *)comImageModelWithUserIconDict:(NSDictionary *)imageDict;

//将评论图片集转化成UMComImageModel类型
+ (UMComImageModel *)comImageModelWithCommentImageDict:(NSDictionary *)imageDict;

//将话题图片集转化成UMComImageModel类型
+ (UMComImageModel *)comImageModelWithTopipImageDict:(NSDictionary *)imageDict;

//将Feed图片集转化成UMComImageModel类型
+ (UMComImageModel *)comImageModelWithFeedImageDict:(NSDictionary *)imageDict;


//将UMComImageModel类型转化成Feed图片的Dictionary结构
+ (NSDictionary *)feedImageDictFromImageModel:(UMComImageModel *)imageModel;

//将UMComImageModel类型转化成评论图片的Dictionary结构
+ (NSDictionary *)commentImageDictFromImageModel:(UMComImageModel *)imageModel;

//将UMComImageModel类型转化成评论用户icon图片的Dictionary结构
+ (NSDictionary *)userIconImageDictFromImageModel:(UMComImageModel *)imageModel;

@end
