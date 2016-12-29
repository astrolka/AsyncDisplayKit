//
//  PhotoFeedSectionController.m
//  Sample
//
//  Created by Adlai Holler on 12/29/16.
//  Copyright © 2016 Facebook. All rights reserved.
//

#import "PhotoFeedSectionController.h"
#import "PhotoFeedModel.h"
#import "PhotoModel.h"
#import "PhotoCellNode.h"

@implementation PhotoFeedSectionController

- (void)didUpdateToObject:(id)object
{
  _photoFeed = object;
}

- (NSInteger)numberOfItems
{
  return [_photoFeed numberOfItemsInFeed];
}

- (ASCellNodeBlock)nodeBlockForItemAtIndex:(NSInteger)index
{
  PhotoModel *photoModel = [_photoFeed objectAtIndex:index];
  // this will be executed on a background thread - important to make sure it's thread safe
  ASCellNode *(^ASCellNodeBlock)() = ^ASCellNode *() {
    PhotoCellNode *cellNode = [[PhotoCellNode alloc] initWithPhotoObject:photoModel];
    return cellNode;
  };

  return ASCellNodeBlock;
}

- (void)beginBatchFetchWithContext:(ASBatchContext *)context
{
  NSInteger oldCount = self.photoFeed.numberOfItemsInFeed;
  [_photoFeed requestPageWithCompletionBlock:^(NSArray *newPhotos){

    [self.collectionContext performBatchAnimated:YES updates:^{
      NSRange range = NSMakeRange(oldCount, newPhotos.count);
      [self.collectionContext insertInSectionController:self atIndexes:[NSIndexSet indexSetWithIndexesInRange:range]];
    } completion:^(BOOL finished) {
      [context completeBatchFetching:YES];
    }];
  } numResultsToReturn:20];
}

- (void)didSelectItemAtIndex:(NSInteger)index
{
  // nop
}

- (void)refreshContentWithCompletion:(void(^)())completion
{
  [_photoFeed refreshFeedWithCompletionBlock:^(NSArray *addedItems) {
    [self.collectionContext reloadSectionController:self];
    if (completion) {
      completion();
    }
  } numResultsToReturn:4];
}

ASIGSectionControllerSizeForItemImplementation;
ASIGSectionControllerCellForIndexImplementation;

@end
