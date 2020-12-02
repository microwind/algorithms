#import <Foundation/Foundation.h>

@interface Factor : NSObject
- (NSArray*)factorize:(int)num;
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"Hi, this is about factor algorithm by Objective-C");
        Factor *factor = [[Factor alloc] init];
        int num = 120;
        NSArray *arr = [factor factorize: num];
        NSLog(@"%@", arr);

        // echo
        NSLog(@"%d = ", num);
        for (id obj in arr)
        {
            NSLog(@"%@ *", obj);
        }

        // echo
        printf("%d = ", num);
        for (int i = 0; i < [arr count]; i++)
        {
            if (i != 0) {
                printf(" * ");
            }
            printf("%d", [arr[i] intValue]);
        }

        }
    return 0;
}

@implementation Factor
- (NSArray*)factorize:(int)num
{
    // NSMutableArray *arr = [NSMutableArray arrayWithCapacity: 100];
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    int i = 2;
    int resultIdx = 0;
    while (i * i < num) {
        while (num % i == 0) {
            [arr addObject: [NSNumber numberWithInt: i]];
            // NSLog(@"%d" @"=" @"%d", i, resultIdx);
            resultIdx++;
            num /= i;
        }
        i++;
    }
    if (num > 1) {
        [arr addObject: [NSNumber numberWithInt: num]];
        NSLog(@"%d", num);
    }
    return arr;
}
@end


/*
jarry@jarrys-MacBook-Pro factor % gcc -lc factor.m -framework Foundation
jarry@jarrys-MacBook-Pro factor % g++ -lc factor.m -framework Foundation
jarry@jarrys-MacBook-Pro factor % cc -lc factor.m -framework Foundation
jarry@jarrys-MacBook-Pro factor % ./a.out 
*/
