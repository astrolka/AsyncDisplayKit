//
//  ASCollectionNode+Beta.h
//  AsyncDisplayKit
//
//  Copyright (c) 2014-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//

#import "ASCollectionNode.h"
@protocol ASCollectionViewLayoutFacilitatorProtocol;
@class IGListAdapter;

NS_ASSUME_NONNULL_BEGIN

@interface ASCollectionNode (Beta)

- (instancetype)initWithFrame:(CGRect)frame collectionViewLayout:(UICollectionViewLayout *)layout layoutFacilitator:(nullable id<ASCollectionViewLayoutFacilitatorProtocol>)layoutFacilitator;

- (void)beginUpdates ASDISPLAYNODE_DEPRECATED_MSG("Use -performBatchUpdates:completion: instead.");

- (void)endUpdatesAnimated:(BOOL)animated ASDISPLAYNODE_DEPRECATED_MSG("Use -performBatchUpdates:completion: instead.");

- (void)endUpdatesAnimated:(BOOL)animated completion:(nullable void (^)(BOOL))completion ASDISPLAYNODE_DEPRECATED_MSG("Use -performBatchUpdates:completion: instead.");

@property (nonatomic, weak) IGListAdapter *listAdapter;

@end

#pragma mark - IGListKit Support

#if IG_LIST_KIT

#define ASIGSectionControllerCellForIndexImplementation \
- (__kindof UICollectionViewCell *)cellForItemAtIndex:(NSInteger)index\
{\
  return [self.collectionContext dequeueReusableCellOfClass:NSClassFromString(@"_ASCollectionViewCell") forSectionController:self atIndex:index];\
}\

#define ASIGSectionControllerSizeForItemImplementation \
- (CGSize)sizeForItemAtIndex:(NSInteger)index \
{\
  return CGSizeZero;\
}

@protocol ASIGListSectionController
- (ASCellNodeBlock)nodeBlockForItemAtIndex:(NSInteger)index;
@end

#endif

NS_ASSUME_NONNULL_END
