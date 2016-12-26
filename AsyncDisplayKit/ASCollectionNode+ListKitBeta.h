
#if IG_LIST_KIT

#import <AsyncDisplayKit/AsyncDisplayKit.h>
#import <IGListKit/IGListKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ASCollectionNode (ListKitBeta)

@property (nonatomic, weak) IGListAdapter *listAdapter;

@end

@protocol ASIGListSectionType <IGListSectionType>

/**
 * A method to provide the node block for the item at the given index.
 * The node block you return will be run asynchronously off the main thread,
 * so it's important to retrieve any objects from your section _outside_ the block
 * because by the time the block is run, the array may have changed.
 *
 * @param index The index of the item.
 * @return A block to be run concurrently to build the node for this item.
 * @see collectionNode:nodeBlockForItemAtIndexPath:
 */
- (ASCellNodeBlock)nodeBlockForItemAtIndex:(NSInteger)index;

@optional

/**
 * A method to provide the constrained size used for measuring the item
 * at the given index.
 *
 * @param index The index of the item.
 * @return A constrained size used for asynchronously measuring the node at this index.
 * @see collectionNode:constrainedSizeForItemAtIndexPath:
 */
- (ASSizeRange)constrainedSizeForItemAtIndex:(NSInteger)index;

@end

@protocol ASIGListSupplementaryViewSource <IGListSupplementaryViewSource>

/**
 * A method to provide the node for the item at the given index.
 *
 * @param elementKind The kind of supplementary element.
 * @param index The index of the item.
 * @return A node for the supplementary element.
 * @see collectionNode:nodeForSupplementaryElementOfKind:atIndexPath:
 */
- (ASCellNode *)nodeForSupplementaryElementOfKind:(NSString *)elementKind atIndex:(NSInteger)index;

@optional

/**
 * A method to provide the constrained size used for measuring the supplementary
 * element of the given kind at the given index.
 *
 * @param elementKind The kind of supplementary element.
 * @param index The index of the item.
 * @return A constrained size used for asynchronously measuring the node.
 * @see collectionNode:constrainedSizeForSupplementaryElementOfKind:atIndexPath:
 */
- (ASSizeRange)constrainedSizeForSupplementaryElementOfKind:(NSString *)elementKind atIndex:(NSInteger)index;

@end

/**
 * The implementation of viewForSupplementaryElementOfKind that connects
 * IGSupplementaryViewSource to AsyncDisplayKit. Add this into the .m file
 * for your `ASIGListSupplementaryViewSource` and implement the ASDK-specific
 * method `nodeForSupplementaryElementOfKind:` to provide your node.
 *
 * @param sectionController The section controller this supplementary source is 
 * working on behalf of. For example, `self` or `self.sectionController`.
 */
#define ASIGSupplementarySourceViewForSupplementaryElementImplementation(sectionController) \
- (__kindof UICollectionReusableView *)viewForSupplementaryElementOfKind:(NSString *)elementKind atIndex:(NSInteger)index { \
  return [self.collectionContext dequeueReusableSupplementaryViewOfKind:elementKind forSectionController:sectionController class:[UICollectionReusableView class] atIndex:index]; \
}

/**
 * The implementation of sizeForSupplementaryViewOfKind that connects
 * IGSupplementaryViewSource to AsyncDisplayKit. Add this into the .m file
 * for your `ASIGListSupplementaryViewSource` and implement the ASDK-specific
 * method `nodeForSupplementaryElementOfKind:` to provide your node which should
 * size itself. You can set `node.style.preferredSize` if you want to fix the size.
 *
 * @param sectionController The section controller this supplementary source is
 * working on behalf of. For example, `self` or `self.sectionController`.
 */
#define ASIGSupplementarySourceSizeForSupplementaryElementImplementation \
- (CGSize)sizeForSupplementaryViewOfKind:(NSString *)elementKind atIndex:(NSInteger)index {\
  ASDisplayNodeFailAssert(@"Did not expect %@ to be called.", NSStringFromSelector(_cmd)); \
  return CGSizeZero; \
}


#define ASIGSectionControllerCellForIndexImplementation \
- (__kindof UICollectionViewCell *)cellForItemAtIndex:(NSInteger)index\
{\
  return [self.collectionContext dequeueReusableCellOfClass:NSClassFromString(@"_ASCollectionViewCell") forSectionController:self atIndex:index]; \
}\

#define ASIGSectionControllerSizeForItemImplementation \
- (CGSize)sizeForItemAtIndex:(NSInteger)index \
{\
  ASDisplayNodeFailAssert(@"Did not expect %@ to be called.", NSStringFromSelector(_cmd)); \
  return CGSizeZero;\
}

NS_ASSUME_NONNULL_END

#endif
