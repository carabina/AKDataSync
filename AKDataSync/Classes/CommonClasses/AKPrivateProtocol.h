//
//  AKPrivateProtocol.h
//  AKDataSync
//
//  Created by Stanislav Pletnev on 11.06.16.
//  Copyright © 2016 Anobisoft.com. All rights reserved.
//


@protocol AKRepresentableTransaction;
@protocol AKDataSyncContextPrivate;
#if TARGET_OS_IOS
@protocol AKCloudManager, AKCloudMappingProvider;
#endif
@protocol AKWatchConnector;

@protocol AKTransactionsAgregator;
@protocol AKWatchTransactionsAgregator;

@class AKCloudMapping;

#ifndef AKPrivateProtocol_h
#define AKPrivateProtocol_h

#import "AKPublicProtocol.h"
#import "AKCloudMapping.h"

#pragma mark - AKDataSyncContextPrivate protocol

@protocol AKRepresentableTransaction <NSObject>
@required

- (NSString *)contextIdentifier;
- (NSSet <NSObject <AKMappedObject> *> *)updatedObjects;
- (NSSet <NSObject <AKDescription> *> *)deletedObjects;

@end

@protocol AKDataSyncContextPrivate <AKRepresentableTransaction>
@required
- (void)performMergeWithTransaction:(id <AKRepresentableTransaction>)transaction;
- (void)setAgregator:(id<AKTransactionsAgregator>)agregator;
@end

#pragma mark - AKCloudManager protocol
#if TARGET_OS_IOS
@protocol AKCloudManager <AKTransactionsAgregator>
@required
- (void)setDataSyncContext:(id <AKDataSyncContextPrivate, AKCloudMappingProvider>)context;
@property (nonatomic, assign) BOOL enabled;
- (void)acceptPushNotificationUserInfo:(NSDictionary *)userInfo;
- (void)smartReplication;
- (void)totalReplication;
- (BOOL)ready;
@end

@protocol AKCloudMappingProvider <NSObject>
- (void)setCloudManager:(id<AKCloudManager>)cloudManager;
- (AKCloudMapping *)cloudMapping;
@end
#endif

#pragma mark - AKWatchConnector protocol

@protocol AKWatchConnector <NSObject>
- (void)setAgregator:(id<AKWatchTransactionsAgregator>)agregator;
- (BOOL)ready;
- (void)sendTransaction:(id <AKRepresentableTransaction, NSCoding>)transaction;
@end


#pragma mark - AKDataAgregator protocol

@protocol AKTransactionsAgregator <NSObject>
@required
- (void)willCommitTransaction:(id <AKRepresentableTransaction>)transaction;
@end

@protocol AKWatchTransactionsAgregator <NSObject>
@required
- (void)watchConnector:(id <AKWatchConnector>)connector didRecieveTransaction:(id <AKRepresentableTransaction>)transaction;
- (void)watchConnectorGetReady:(id <AKWatchConnector>)connector;
@end

#endif /* AKPrivateProtocol_h */
