//
//  UMComHttpManager.h
//  UMCommunity
//
//  Created by luyiyuan on 14/8/27.
//  Copyright (c) 2014年 luyiyuan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "UMComUserAccount.h"
#import "UMComTools.h"

/**
 feed的评论列表排序类型
 
 */
typedef enum {
    commentorderByDefault = 0,//默认按时间倒序排序
    commentorderByTimeDesc = 1,//按时间倒序排序
    commentorderByTimeAsc = 2 //按时间正序排序
}UMComCommentSortType;

/**
 话题所有feed的排序类型
 
 */
typedef enum{
    UMComFeedSortTypeDefault,
    UMComFeedSortTypeComment,   //评论时间
    UMComFeedSortTypeLike,      //赞时间
    UMComFeedSortTypeForward,     //转发时间
    UMComFeedSortTypeAction,       //评论或赞或转发时间
}UMComFeedSortType;

/**
 用户个人feed列表的排序类型
 
 */
typedef enum {
    UMComTimeLineTypeDefault = 0,//默认返回所有feed
    UMComTimeLineTypeOrigin = 1,//只获取原feed，不带转发
    UMComTimeLineTypeForward = 2//只获取转发的feed
}UMComTimeLineType;


typedef void (^RequestCompletedNoPageResponse)(id responseObject, NSError *error);

@interface UMComHttpManager : NSObject

+ (UMComHttpManager *)shareInstance;

/****************************GET Method*****************************************/

//获取下一页请求
+ (void)getRequestNextPageWithNextPageUrl:(NSString *)urlString
                                 response:(PageDataResponse)response;


#pragma mark - Feed
//获取最新的Feed列表
+ (void)getAllNewFeedsWithCount:(NSInteger)count
                       response:(PageDataResponse)response;

//获取用户关注的Feed列表
+ (void)getUserFocusFeedsWithCount:(NSInteger)count
                          response:(PageDataResponse)response;
//获取推荐Feed列表
+ (void)getRecommendFeedsWithCount:(NSInteger)count
                          response:(PageDataResponse)response;

//获取好友的Feed列表
+ (void)getFriendFeedsWithCount:(NSInteger)count
                       response:(PageDataResponse)response;

//获取keywords相关的Feed列表
+ (void)getSearchFeedsWithCount:(NSInteger)count
                       keywords:(NSString *)keywords
                       response:(PageDataResponse)response;

//获取附近的Feed列表
+ (void)getNearbyFeedsWithCount:(NSInteger)count
                       location:(CLLocation *)location
                       response:(PageDataResponse)response;

//获取对应feedIds列表对应的Feed列表
+ (void)getFeedsWithFeedIds:(NSArray *)feedIds
                   response:(PageDataResponse)response;

//获取单个
+ (void)getOneFeedWithFeedId:(NSString *)feedId
                   commentId:(NSString *)commentId
                    response:(PageDataResponse)response;

//获取用户时间轴的Feed列表
+ (void)getUserTimelineWithCount:(NSInteger)count
                            fuid:(NSString *)fuid
                        sortType:(UMComTimeLineType)sortType
                        response:(PageDataResponse)response;

//获取用户被@的Feed列表
+ (void)getUserBeAtFeedWithCount:(NSInteger)count
                        response:(PageDataResponse)response;

//获取用户收藏的Feed列表
+ (void)getUserFavouriteFeedsWithCount:(NSInteger)count
                              response:(PageDataResponse)response;

//获取话题相关的Feed列表
+ (void)getTopicRelatedFeedsWithCount:(NSInteger)count
                              topicId:(NSString *)topicId
                             sortType:(UMComFeedSortType)sortType
                            isReverse:(BOOL)isReverse
                             response:(PageDataResponse)response;

//获取该话题下推荐feed列表
+ (void)getTopicRecommendFeedsWithCount:(NSInteger)count
                                topicId:(NSString *)topicId
                               response:(PageDataResponse)response;


#pragma mark - user

//获取keywords相关的用户列表
+ (void)getSearchUsersWithCount:(NSInteger)count
                       keywords:(NSString *)keywords
                       response:(PageDataResponse)response;

//获取某个话题相关的活跃用户列表
+ (void)getTopicActiveUsersWithCount:(NSInteger)count
                             topicId:(NSString *)topicId
                            response:(PageDataResponse)response;

//获取推荐的用户列表
+ (void)getRecommentUsersWithCount:(NSInteger)count
                          response:(PageDataResponse)response;

//获取某个用户的粉丝列表
+ (void)getUserFansWithCount:(NSInteger)count
                        fuid:(NSString *)fuid
                    response:(PageDataResponse)response;

//获取某个用户关注的人的列表
+ (void)getUserFollowingsWithCount:(NSInteger)count
                              fuid:(NSString *)fuid
                          response:(PageDataResponse)response;

//获取某个用户的详细信息
+ (void)getUserProfileWithFuid:(NSString *)fuid
                        source:(NSString *)source
                    source_uid:(NSString *)source_uid
                      response:(PageDataResponse)response;


#pragma mark - topic

//获取所有的话题列表
+ (void)getAllTopicsWithCount:(NSInteger)count
                     response:(PageDataResponse)response;

//获取keywords相关的话题列表
+ (void)getSearchTopicsWithCount:(NSInteger)count
                        keywords:(NSString *)keywords
                        response:(PageDataResponse)response;
//获取某个用户关注的话题列表
+ (void)getUserFocusTopicsWithCount:(NSInteger)count
                               fuid:(NSString *)fuid
                           response:(PageDataResponse)response;

//获取推荐话题
+ (void)getRecommendTopicsWithCount:(NSInteger)count
                           response:(PageDataResponse)response;


#pragma mark - like
//获取某个Feed的点赞列表
+ (void)getFeedLikesWithCount:(NSInteger)count
                       feedId:(NSString *)feedId
                     response:(PageDataResponse)response;
//获取用户点赞列表
+ (void)getUserLikesReceivedWithCount:(NSInteger)count
                             response:(PageDataResponse)response;



#pragma mark - comment

//获取某个Feed的评论列表
+ (void)getFeedCommentsWithCount:(NSInteger)count
                          feedId:(NSString *)feedId
                        sortType:(UMComCommentSortType)sortType
                        response:(PageDataResponse)response;

//获取用户收到的评论列表
+ (void)getUserCommentsReceivedWithCount:(NSInteger)count
                                response:(PageDataResponse)response;

//获取用户写过的评论列表
+ (void)getUserCommentsSentWithCount:(NSInteger)count
                            response:(PageDataResponse)response;



#pragma mark - notification
//获取用户通知列表
+ (void)getUserNotificationWithCount:(NSInteger)count
                            response:(PageDataResponse)response;


#pragma mark - album
//获取用户相册列表
+ (void)getUserAlbumWithCount:(NSInteger)count
                         fuid:(NSString *)fuid
                     response:(PageDataResponse)response;


#pragma mark - other

//获取未读feed消息数
+ (void)unreadFeedCountWithSeq:(NSNumber *)seq resultBlock:(RequestCompletedNoPageResponse)response;

//获取未读消息数
//+ (void)unreadMessageCountWithUid:(NSString *)uid resultBlock:(RequestCompletedNoPageResponse)response;

// 获取 地理位置数据
+ (void)getLocationNames:(CLLocationCoordinate2D)coordinate
             response:(RequestCompletedNoPageResponse)response;

// 获取配置数据
+ (void)getConfigDataWithResponse:(RequestCompletedNoPageResponse)response;

/****************************POST Method*****************************************/


#pragma mark -
#pragma mark User

//用户登录

+ (void)userLoginWithName:(NSString *)name
                   source:(NSString *)source
                 sourceId:(NSString *)sourceId
                 icon_url:(NSString *)icon_url
                   gender:(NSNumber *)gender
                      age:(NSNumber *)age
                   custom:(NSString *)custom
                    score:(NSNumber *)score
               levelTitle:(NSString *)levelTitle
                    level:(NSNumber *)level
             userNameType:(UMComUserNameType)userNameType
           userNameLength:(UMComUserNameLength)userNameLength
                 response:(RequestCompletedNoPageResponse)response;

//关注和取消关注用户
+ (void)userFollow:(NSString *)uid isFollow:(BOOL)isFollow response:(RequestCompletedNoPageResponse)response;

//修改用户资料
+ (void)updateProfileWithName:(NSString *)name
                          age:(NSNumber *)age
                       gender:(NSNumber *)gender
                     icon_url:(NSString *)icon_url
                     response:(RequestCompletedNoPageResponse)response;

//修改用户头像
+ (void)updateProfileImage:(UIImage *)icon response:(RequestCompletedNoPageResponse)response;

//检查用户名是否合法
+ (void)checkUserName:(NSString *)name userNameType:(UMComUserNameType)userNameType userNameLength:(UMComUserNameLength)userNameLength resultBlock:(void (^)(id responseObject, NSError *))response;

//举报用户
+ (void)spamUser:(NSString *)userId response:(RequestCompletedNoPageResponse)response;


#pragma mark -
#pragma mark feeds

//创建 feed（发消息）
+ (void)createFeed:(NSDictionary *)parameters response:(RequestCompletedNoPageResponse)response;

+ (void)postImage:(UIImage *)image response:(RequestCompletedNoPageResponse)response;

//点赞某个feed或取消
+ (void)likeFeed:(NSString *)feedId isLike:(BOOL)isLike response:(RequestCompletedNoPageResponse)response;

//对某 feed 转发
+ (void)forwardFeed:(NSString *)feedId
            content:(NSString *)content
        relatedUids:(NSArray *)uids
       locationName:(NSString *)location
      locationPoint:(CLLocationCoordinate2D *)coordinate
           feedType:(NSNumber *)type
           response:(RequestCompletedNoPageResponse)response;

//举报feed
+ (void)spamFeed:(NSString *)feedId response:(RequestCompletedNoPageResponse)response;

//删除feed
+ (void)deleteFeed:(NSString *)feedId response:(RequestCompletedNoPageResponse)response;


//收藏某个feed操作/取消收藏某个feed操作
+ (void)favouriteFeedWithFeedId:(NSString *)feedId isFavourite:(BOOL)isFavourite resultBlock:(RequestCompletedNoPageResponse)response;

//对某 feed 发表评论
+ (void)commentFeed:(NSString *)centent feedID:(NSString *)feedID replyUid:(NSString *)commentUid response:(RequestCompletedNoPageResponse)response;

//统计分享信息
+ (void)shareCallback:(NSString *)platform feedId:(NSString *)feedId response:(RequestCompletedNoPageResponse)response;


#pragma mark -
#pragma mark comments
//举报feed的评论
+ (void)spamComment:(NSString *)commentId response:(RequestCompletedNoPageResponse)response;

//删除feed的评论
+ (void)deleteComment:(NSString *)commentId feedId:(NSString *)feedId response:(RequestCompletedNoPageResponse)response;

#pragma mark -
#pragma mark topic
//关注或取消关注某个话题
+ (void)topicFocuseWithTopicId:(NSString *)topicId isFollow:(BOOL)isFollow response:(RequestCompletedNoPageResponse)response;


@end
