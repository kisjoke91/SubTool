//
//  Wrapper.mm
//  test
//
//  Created by Szigeti József on 09.01.21.
//

#import "Wrapper.h"
#import "subtool.h"


@implementation SRTFrame
@end

@implementation SubTool {
    Subtool t;
}

- (void) importFileContent: (NSString *) lines {
    self->t.getMainFileFromString([lines cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (void) shiftGlobalTiming: (long) offset {
    self->t.shiftTimingOfMainFile(offset);
}

- (NSString *) getOutput {
    return [NSString stringWithCString:self->t.getOutput().c_str() encoding:[NSString defaultCStringEncoding]];
}

- (SRTFrame *) getFrame: (int) frameID {
    
    SRTFrame * f = [SRTFrame new];
    srt_frame_t n;
    
    n = self->t.getFrameFromMainFile(frameID);
    
    if (n.id == SRT_INVALID_ID) {
        return nil;
    }
    
    f->frameid = n.id;
    f->startTime = n.startTime;
    f->endTime = n.endTime;
    f->content = [NSString stringWithCString:n.content.c_str() encoding:[NSString defaultCStringEncoding]];
    
    return f;
}

- (SRTError) addFrame: (SRTFrame *) frame {
    
    srt_frame_t f;
    
    f.id = frame->frameid;
    f.startTime = frame->startTime;
    f.endTime = frame->endTime;
    f.content = [frame->content cStringUsingEncoding:NSUTF8StringEncoding];
    
    return (SRTError) self->t.addFrameToMainFile(f);
}

- (SRTError) setFrame: (SRTFrame *) frame {
    
    srt_frame_t f;
    
    f.id = frame->frameid;
    f.startTime = frame->startTime;
    f.endTime = frame->endTime;
    f.content = [frame->content cStringUsingEncoding:NSUTF8StringEncoding];
    
    return (SRTError) self->t.setFrameInMainFile(f);
}

- (BOOL) removeFrame: (int) frameID {
    return self->t.removeFrameFromMainFile(frameID);
}

- (NSArray <SRTFrame *> *) frames {
    
    NSMutableArray * a = [NSMutableArray new];

    for(auto n: self->t.mainFile) {
        
        SRTFrame * f = [SRTFrame new];
        
        f->frameid = n.id;
        f->startTime = n.startTime;
        f->endTime = n.endTime;
        f->content = [NSString stringWithCString:n.content.c_str() encoding:[NSString defaultCStringEncoding]];
        
        [a addObject: f];
    }

    return a;
}

@end
