//
//  AKDevice.h
//  AKDataSync
//
//  Created by Stanislav Pletnev on 2016-12-21
//  Copyright © 2016 Anobisoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AKObjectRepresentation.h"

@interface AKDevice : AKObjectRepresentation <AKMutableMappedObject, AKMutableReference>

+ (instancetype)deviceWithMappedObject:(id <AKMappedObject>)mappedObject;

- (void)setUUID:(NSUUID *)UUID;
- (void)setUUIDString:(NSString *)UUIDString;

@end
