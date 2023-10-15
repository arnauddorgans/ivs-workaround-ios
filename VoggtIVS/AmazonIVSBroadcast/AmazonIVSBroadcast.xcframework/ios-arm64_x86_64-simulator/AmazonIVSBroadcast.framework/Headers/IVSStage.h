//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>
#import <AmazonIVSBroadcast/IVSErrorSource.h>

@protocol IVSStageRenderer;
@protocol IVSStageStrategy;

NS_ASSUME_NONNULL_BEGIN

/// The various possible connection states for a Stage.
typedef NS_ENUM(NSInteger, IVSStageConnectionState) {
    /// The associated `IVSStage` is not connected to a Stage
    IVSStageConnectionStateDisconnected = 0,
    /// The associated `IVSStage` is establishing a connection to the Stage
    IVSStageConnectionStateConnecting = 1,
    /// The associated `IVSStage` is connected to the Stage
    IVSStageConnectionStateConnected = 2,
};


IVS_EXPORT
API_AVAILABLE(ios(14))
/// The main interaction point for interacting with the Stage SDK.
@interface IVSStage : NSObject <IVSErrorSource>

/// Creates an `IVSStage` with the provided token.
///
/// @note The `IVSStage` holds a weak reference to the `IVSStageStrategy` object.
///
/// @param token A token acquired by the IVS control plane, used to connect to a Stage.
/// @param strategy The strategy used by this stage to make decisions. See `IVSStageStrategy` for more information.
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
- (nullable instancetype)initWithToken:(NSString *)token
                              strategy:(id<IVSStageStrategy>)strategy
                                 error:(NSError *__autoreleasing *)outError;

/// Joins the Stage associated with the token provided during initialization.
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
- (BOOL)joinWithError:(NSError *__autoreleasing *)outError;

/// Leave the current Stage
- (void)leave;

/// Adds a renderer to the list of renderers that will be notified of updates to the Stage.
/// @param renderer The renderer to add.
- (void)addRenderer:(id<IVSStageRenderer>)renderer NS_SWIFT_NAME(addRenderer(_:));

/// Removes a renderer to the list of renderers that will be notified of updates to the Stage.
/// @param renderer The renderer to remove.
- (void)removeRenderer:(id<IVSStageRenderer>)renderer;

/// Asynchronously sets the strategy used by this `IVSStage`. See `IVSStageStrategy` for more information.
///
/// @note The `IVSStage` holds a weak reference to the `IVSStageStrategy` object.
///
/// @param strategy The new strategy to use with the Stage.
- (void)replaceStrategy:(id<IVSStageStrategy>)strategy NS_SWIFT_NAME(replaceStrategy(_:));

/// Triggers the `IVSStageStrategy` on this instance to refresh its state. This is how host applications will make changes to how they are interacting with a Stage.
- (void)refreshStrategy;

@end

NS_ASSUME_NONNULL_END
