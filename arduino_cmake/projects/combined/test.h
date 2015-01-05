/*
 * test.h
 * 
 * An example of how you would use a .c header file in your Arduino project
 * 
 */

#ifndef TEST_H_
#define TEST_H_

#ifdef __cplusplus
extern "C" {
#endif


#define TEST 'a'
void test(char c);


#ifdef __cplusplus
}
#endif

#endif // TEST_H_
