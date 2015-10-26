//
//  UMComFeed.h
//  UMCommunity
//
//  Created by umeng on 15/10/22.
//  Copyright © 2015年 Umeng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "UMComManagedObject.h"

#define FeedStatusDeleted 2

@class UMComComment, UMComLike, UMComTopic, UMComUser;


@interface UMComFeed : UMComManagedObject

@property (nullable, nonatomic, retain) NSNumber *comments_count;
@property (nullable, nonatomic, retain) NSString *create_time;
@property (nullable, nonatomic, retain) NSString *custom;
@property (nullable, nonatomic, retain) NSNumber *distance;
@property (nullable, nonatomic, retain) NSString *feedID;
@property (nullable, nonatomic, retain) NSNumber *forward_count;
@property (nullable, nonatomic, retain) NSNumber *has_collected;
@property (nullable, nonatomic, retain) id images;
@property (nullable, nonatomic, retain) NSString *is_follow;
@property (nullable, nonatomic, retain) NSNumber *is_top;
@property (nullable, nonatomic, retain) NSNumber *is_recommend;
@property (nullable, nonatomic, retain) NSNumber *liked;
@property (nullable, nonatomic, retain) NSNumber *likes_count;
@property (nullable, nonatomic, retain) id location;
@property (nullable, nonatomic, retain) NSString *origin_feed_id;
@property (nullable, nonatomic, retain) NSString *parent_feed_id;
@property (nullable, nonatomic, retain) NSNumber *seq;
@property (nullable, nonatomic, retain) NSNumber *seq_recommend;
@property (nullable, nonatomic, retain) NSNumber *share_count;
@property (nullable, nonatomic, retain) NSString *share_link;
@property (nullable, nonatomic, retain) NSNumber *source_mark;
@property (nullable, nonatomic, retain) NSNumber *status;
@property (nullable, nonatomic, retain) NSString *text;
@property (nullable, nonatomic, retain) NSString *title;
@property (nullable, nonatomic, retain) NSNumber *type;
@property (nullable, nonatomic, retain) NSOrderedSet<UMComComment *> *comments;
@property (nullable, nonatomic, retain) UMComUser *creator;
@property (nullable, nonatomic, retain) NSOrderedSet<UMComFeed *> *forward_feeds;
@property (nullable, nonatomic, retain) NSOrderedSet<UMComLike *> *likes;
@property (nullable, nonatomic, retain) UMComFeed *origin_feed;
@property (nullable, nonatomic, retain) NSOrderedSet<UMComUser *> *related_user;
@property (nullable, nonatomic, retain) NSOrderedSet<UMComTopic *> *topics;

@end


