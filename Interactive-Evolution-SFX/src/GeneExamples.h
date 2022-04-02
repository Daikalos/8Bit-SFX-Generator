//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

#pragma once

#include <string>

static const std::string examples[15] =
{
	R"(poke 24 14
poke 1 130
poke 5 9
poke 15 30
poke 4 21
sample 1000
poke 4 20
sample 1000)",

	R"(poke 24 14 
poke 21 3
poke 18 81
poke 6 11
poke 13 81
poke 17 61
poke 16 77
sample 276
poke 1 80
poke 3 21
sample 175
poke 17 80
poke 18 31
poke 9 12
poke 4 17
poke 19 23
sample 23
poke 5 90
poke 14 54
poke 7 87
poke 4 22
poke 1 52
poke 12 33
poke 16 73
poke 11 22
sample 189
poke 10 55
poke 1 44
sample 663
poke 15 2
poke 6 7
sample 851)",

	R"(poke 24 14
poke 20 9
poke 19 83
poke 3 38
poke 9 85
poke 21 33
poke 7 82
sample 56
poke 11 21
poke 2 63
poke 1 11
poke 15 81
poke 9 78
poke 3 66
poke 10 68
poke 20 58
poke 12 46
sample 572)",

	R"(poke 24 14
poke 7 87
poke 11 17
poke 21 46
poke 10 6
poke 6 94
poke 12 25
poke 3 78
poke 4 54
poke 8 29
poke 9 68
poke 17 79
poke 2 14
poke 18 21
poke 13 41
poke 19 72
poke 16 61
poke 20 4
poke 15 34
sample 1200)",

	R"(poke 24 14
poke 22 26
poke 4 1
poke 7 31
poke 23 9
poke 2 15
poke 6 7
poke 5 26
poke 15 91
poke 14 14
poke 16 73
poke 21 10
poke 3 91
poke 18 21
poke 8 10
poke 19 58
poke 0 43
poke 20 34
poke 13 6
sample 1448
poke 7 84
poke 6 45
sample 635)",

	R"(poke 24 14
poke 4 11
poke 1 43
poke 3 72
poke 0 17
poke 7 62
poke 17 45
poke 21 95
poke 18 21
poke 20 0
poke 8 37
poke 10 30
poke 13 46
poke 14 23
poke 19 75
poke 5 94
sample 644
poke 1 85
poke 17 95
poke 22 18
poke 0 61
poke 14 52
poke 13 34
sample 389)",

	R"(poke 24 14
poke 6 40
poke 1 62
poke 22 32
poke 18 19
poke 12 89
poke 10 43
poke 19 38
poke 20 13
poke 9 38
poke 3 50
poke 15 50
poke 0 7
poke 18 22
poke 21 22
poke 7 33
poke 8 14
poke 17 98
poke 13 86
poke 7 45
poke 16 62
poke 6 84
sample 391
poke 4 42
poke 13 91
poke 20 76
poke 10 91
poke 21 46
poke 6 11
poke 2 10
poke 23 64
poke 19 27
poke 13 95
poke 6 94
poke 20 45
poke 6 59
poke 9 85
poke 14 36
poke 7 80
poke 17 36
poke 4 100
poke 5 85
poke 1 15
poke 17 52
poke 8 84
poke 5 63
poke 10 23
poke 21 41
poke 6 22
poke 23 56
poke 1 14
poke 12 49
poke 3 28
poke 16 63
poke 0 89
poke 7 20
poke 9 93
poke 15 33
poke 20 9
poke 11 10
poke 22 66
poke 4 25
sample 51
poke 16 85
poke 21 60
sample 791)",

	R"(poke 24 14
poke 14 38
poke 19 46
poke 13 47
poke 22 75
poke 3 67
poke 17 74
poke 16 87
poke 14 8
poke 4 29
poke 6 67
poke 20 51
poke 2 11
poke 10 15
poke 19 82
poke 12 83
poke 15 2
sample 61
poke 19 2
poke 4 1
poke 4 21
poke 14 51
poke 8 3
poke 17 39
sample 46
poke 7 18
poke 21 8
poke 9 58
poke 16 78
poke 6 79
sample 351
poke 20 36
poke 2 26
poke 4 28
poke 7 64
poke 8 93
poke 19 29
poke 12 7
poke 14 94
poke 11 91
poke 17 55
poke 16 26
poke 1 18
poke 9 21
sample 629
poke 22 52
poke 15 21
poke 0 61
poke 17 58
poke 23 100
poke 6 58
sample 678
poke 9 2
poke 15 8
poke 17 49
sample 802)",

	R"(poke 24 14
poke 18 22
poke 5 9
poke 15 30
poke 4 21
poke 10 81
poke 17 74
poke 16 87
poke 21 56
poke 4 29
poke 6 67
poke 20 51
poke 2 11
poke 10 15
poke 19 82
sample 364
poke 1 50
poke 7 38
poke 19 96
poke 14 43
poke 4 21
poke 14 52
poke 9 31
poke 15 25
poke 14 48
sample 878
poke 7 19
poke 9 58
poke 20 17
poke 21 67
poke 3 98
sample 491
poke 2 26
poke 2 68
poke 7 64
poke 8 93
poke 19 29
poke 12 7
poke 2 75
poke 15 19
poke 21 41
poke 6 22
poke 23 56
sample 236
poke 16 61
poke 15 90
poke 4 16
sample 133
poke 17 49
sample 802)",

	R"(poke 24 14
poke 15 30
poke 22 21
poke 18 58
poke 3 37
poke 16 47
poke 18 21
poke 7 30
poke 16 104
poke 9 68
poke 21 30
poke 13 19
poke 2 15
poke 3 85
poke 20 11
poke 4 20
poke 0 118
poke 12 24
poke 11 89
poke 20 3
poke 7 23
poke 19 77
sample 727
poke 1 57
poke 10 36
poke 0 64
poke 17 49
poke 4 20
poke 14 17
poke 15 22
sample 187
poke 14 98
poke 1 99
sample 423
poke 8 31
poke 19 55
poke 5 0
poke 11 8
sample 758
poke 14 46
poke 19 71
poke 2 58
sample 239
poke 12 72
poke 10 14
sample 170
poke 11 25)",

	R"(poke 24 14
poke 10 28
poke 5 41
poke 17 92
poke 14 83
poke 8 44
poke 15 44
poke 4 21
poke 14 28
poke 12 106
poke 9 50
poke 1 2
poke 16 30
poke 8 8
poke 7 39
poke 11 92
poke 6 68
poke 0 115
poke 8 62
poke 2 28
poke 11 94
poke 8 116
poke 21 20
poke 12 54
poke 5 9
sample 372
poke 3 95
poke 15 113
poke 22 66
poke 8 30
poke 1 64
poke 4 20
poke 21 30
poke 11 14
poke 4 20
poke 20 113
sample 157
poke 17 17
poke 20 46
poke 9 76
poke 18 58
poke 16 25
poke 19 85
poke 9 95
poke 22 107
poke 13 101
poke 5 42
poke 5 113
poke 21 53
poke 22 13
poke 21 95
poke 2 100
sample 213
poke 18 93
poke 3 89
poke 13 90
sample 569)",

	R"(poke 24 14
poke 11 89
poke 21 22
poke 3 85
poke 1 2
poke 12 89
poke 4 20
poke 21 31
poke 19 140
poke 14 28
poke 0 118
poke 13 13
poke 20 109
poke 17 92
poke 16 30
poke 7 45
poke 18 21
poke 9 68
poke 15 43
poke 5 76
poke 10 3
poke 1 2
sample 400
poke 17 74
poke 2 12
poke 1 54
poke 14 17
poke 2 41
poke 3 28
poke 5 74
poke 13 95
poke 11 14
poke 1 64
poke 21 30
poke 15 8
poke 22 47
poke 4 20
poke 22 66
poke 2 11
poke 10 112
poke 10 36
poke 15 22
sample 159
poke 15 24
poke 5 50
poke 21 58
poke 20 46
poke 11 28
poke 2 89
poke 1 101
poke 11 11
poke 16 42
poke 21 95
poke 2 27
poke 13 19
poke 7 12
poke 12 1
sample 424
poke 9 10
poke 12 72
poke 13 19
sample 424)",

	R"(poke 24 14
poke 7 24
poke 8 16
poke 9 50
poke 20 83
poke 15 20
poke 20 64
poke 10 76
poke 14 26
poke 21 22
poke 8 31
poke 16 116
poke 22 20
poke 13 41
poke 7 108
poke 18 21
poke 22 32
poke 5 1
poke 0 85
poke 5 11
poke 8 58
poke 4 9
poke 9 29
poke 0 108
poke 6 74
poke 4 21
poke 10 12
poke 15 30
poke 19 72
poke 10 6
poke 6 47
sample 780
poke 18 114
poke 4 20
poke 8 118
poke 2 80
poke 3 124
poke 8 55
poke 11 130
poke 20 47
poke 3 78
poke 18 57
poke 5 136
poke 11 49
poke 8 10
sample 378)",

	R"(poke 24 14
poke 1 14
poke 2 14
poke 4 13
poke 11 0
poke 21 33
poke 8 45
poke 13 111
poke 18 21
poke 16 44
poke 20 9
poke 3 32
poke 9 85
poke 18 21
poke 19 72
poke 5 108
poke 15 0
poke 4 135
poke 13 41
poke 18 52
poke 1 10
poke 3 38
poke 18 21
poke 7 82
sample 922
poke 1 11
poke 9 89
poke 3 67
poke 13 34
poke 22 44
poke 20 53
poke 20 35
poke 15 40
poke 8 74
poke 12 19
poke 11 21
poke 2 64
poke 9 78
poke 12 95
poke 21 65
poke 13 24
poke 5 136
poke 14 15
poke 17 54
poke 12 49
sample 459
poke 20 59
poke 4 135
poke 15 5
poke 4 18
sample 149
poke 11 13
poke 14 124
sample 220
poke 5 129
sample 129)",

	R"(poke 24 14
poke 7 15
poke 11 17
poke 11 132
poke 15 36
poke 6 94
poke 12 25
poke 3 78
poke 4 54
poke 8 29
poke 9 68
poke 17 79
poke 2 14
poke 18 21
poke 13 41
poke 19 72
poke 15 2
sample 61
poke 19 2
poke 4 1
poke 4 21
poke 14 51
poke 8 3
poke 17 39
sample 46
poke 7 18
poke 18 63
poke 9 58
poke 16 78
poke 6 79
sample 351
poke 20 36
poke 2 26
poke 4 28
poke 7 64
poke 8 93
poke 19 29
poke 12 7
poke 14 94
poke 11 91
poke 17 55
poke 16 26
poke 1 18
poke 9 21
poke 5 50
poke 13 19
poke 7 12
poke 0 61
sample 202
poke 17 49
sample 240)"
};
