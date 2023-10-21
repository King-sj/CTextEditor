/* ==================================================================
* Copyright (c) 2023-10-20.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the
* distribution.
* 3. All advertising materials mentioning features or use of this software
* must display the following acknowledgement:
* This product includes software developed by the SJ Group. and
* its contributors.
* 4. Neither the name of the Group nor the names of its contributors may
* be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY SJ,GROUP AND CONTRIBUTORS
* ===================================================================
* Author: KSJ.
*/
#include"gtest/gtest.h"
extern "C"{
#include"sstring.h"
}
TEST(SString, baseFuncTest) {
    SString* a = newSString(50);
    EXPECT_EQ(a->bufferSize, 100);
    EXPECT_EQ(a->length, 0);

    char s[][10] = {{"abs"}, {"abs"}, {"ab"}};
    EXPECT_FALSE(isEqualChars(s[0], s[2]));
    EXPECT_TRUE(isEqualChars(s[0], s[1]));

    fillSString(a, s[0], 100);
    EXPECT_FALSE(isEqualChars(a->data, s[2]));
    EXPECT_TRUE(isEqualChars(a->data, s[1]));

    SString* b = newSString(1);
    copySString(a, b);
    EXPECT_TRUE(isEqualSString(a, b));
    fillSString(b, "100", 4);
    EXPECT_FALSE(isEqualSString(a, b));
}
