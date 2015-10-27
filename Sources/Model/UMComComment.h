//
//  UMComComment.h
//  UMCommunity
//
//  Created by umeng on 15/10/15.
//  Copyright © 2015年 Umeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "UMComManagedObject.h"

@class UMComFeed, UMComUser;

@interface UMComComment : UMComManagedObject

@property (nullable, nonatomic, retain) NSString *commentID;
@property (nullable, nonatomic, retain) NSString *content;
@property (nullable, nonatomic, retain) NSString *create_time;
@property (nullable, nonatomic, retain) NSString *custom;
@property (nullable, nonatomic, retain) NSNumber *likes_count;
@property (nullable, nonatomic, retain) NSNumber *seq;
@property (nullable, nonatomic, retain) NSNumber *status;
@property (nullable, nonatomic, retain) NSNumber *liked;
@property (nullable, nonatomic, retain) id image_urls;
@property (nullable, nonatomic, retain) UMComUser *creator;
@property (nullable, nonatomic, retain) UMComFeed *feed;
@property (nullable, nonatomic, retain) UMComUser *reply_user;

@end

