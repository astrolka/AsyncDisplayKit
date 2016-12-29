//
//  PhotoFeedSectionController.h
//  Sample
//
//  Created by Adlai Holler on 12/29/16.
//  Copyright © 2016 Facebook. All rights reserved.
//

#import <IGListKit/IGListKit.h>
#import <AsyncDisplayKit/AsyncDisplayKit.h>
#import "RefreshingSectionControllerType.h"

@class PhotoFeedModel;

NS_ASSUME_NONNULL_BEGIN

@interface PhotoFeedSectionController : IGListSectionController <ASIGListSectionType, RefreshingSectionControllerType>

@property (nonatomic, strong, nullable) PhotoFeedModel *photoFeed;

@end

NS_ASSUME_NONNULL_END
