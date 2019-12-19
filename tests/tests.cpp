#include "pch.h"
#include "Cube.h"

constexpr unsigned CUBE_SIZE = 3;

TEST(RotateFaceTests, rotateCW) {
  Face face(CUBE_SIZE);

  face.rotateCW();

  EXPECT_EQ(face.faceRotation(), 1);
  for (int row = CUBE_SIZE; row--;) {
    for (int col = CUBE_SIZE; col--;) {
      EXPECT_EQ(face.getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
      EXPECT_EQ(face.getC(row, CUBE_SIZE - 1 - row).rot, 1);
    }
  }
}

TEST(RotateFaceTests, rotateCCW) {
	Face face(CUBE_SIZE);

  face.rotateCCW();

  EXPECT_EQ(face.faceRotation(), 3);
  for (int row = CUBE_SIZE; row--;) {
    for (int col = CUBE_SIZE; col--;) {
      EXPECT_EQ(face.getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
      EXPECT_EQ(face.getC(CUBE_SIZE - 1 - col, row).rot, 3);
    }
  }
}

TEST(RotateFaceTests, rotateTwice) {
	Face face(CUBE_SIZE);

  face.rotateTwice();

  EXPECT_EQ(face.faceRotation(), 2);
  for (int row = CUBE_SIZE; row--;) {
    for (int col = CUBE_SIZE; col--;) {
      EXPECT_EQ(face.getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
      EXPECT_EQ(face.getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).rot, 2);
    }
  }
}

TEST(RotateCubeTests, Identity) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'W','B','G','O','R','Y' };
  int rots[] = { 0,0,0,0,0,0 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = CUBE_SIZE; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, 0);
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeUp) {
  Cube cube(CUBE_SIZE);
  Cubelet::color_t sides[] = { 'G','W','Y','O','R','B' };
  int rots[] = { 0,0,2,3,1,2 };

  cube.rotateCubeUp();
  
  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeDown) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'B','Y','W','O','R','G' };
  int rots[] = { 0,2,0,1,3,2 };

  cube.rotateCubeDown();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeLeft) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'R','B','G','W','Y','O' };
  int rots[] = { 0,1,3,0,0,0 };

  cube.rotateCubeLeft();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeRight) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'O','B','G','Y','W','R' };
  int rots[] = { 0,3,1,0,0,0 };

  cube.rotateCubeRight();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeSpinCW) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'W','O','R','G','B','Y' };
  int rots[] = { 1,1,1,1,1,3 };

  cube.rotateCubeSpinCW();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeSpinCCW) {
  Cube cube(CUBE_SIZE);
  Cubelet::color_t sides[] = { 'W','R','O','B','G','Y' };
  int rots[] = { 3,3,3,3,3,1 };

  cube.rotateCubeSpinCCW();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeUp2) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'Y','G','B','O','R','W' };
  int rots[] = { 2,0,0,2,2,2 };

  cube.rotateCubeUp2();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeLeft2) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'Y','B','G','R','O','W' };
  int rots[] = { 0,2,2,0,0,0 };

  cube.rotateCubeLeft2();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateCubeTests, rotateCubeSpin2) {
	Cube cube(CUBE_SIZE);
	Cubelet::color_t sides[] = { 'W','G','B','R','O','Y' };
  int rots[] = { 2,2,2,2,2,2 };

  cube.rotateCubeSpin2();

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateColumnUp) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateColumnUp(slice);
  }

  // rotateCubeUp() test repeated here

  Cubelet::color_t sides[] = { 'G','W','Y','O','R','B' };
  int rots[] = { 0,0,2,3,1,2 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateColumnDown) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateColumnDown(slice);
  }

  // rotateCubeDown() test repeated here

  Cubelet::color_t sides[] = { 'B','Y','W','O','R','G' };
  int rots[] = { 0,2,0,1,3,2 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row]));
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]);
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]);
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col);
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col);
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col);
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col);
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateColumnTwice) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateColumnTwice(slice);
  }

  // rotateCubeUp2() test repeated here

  Cubelet::color_t sides[] = { 'Y','G','B','O','R','W' };
  int rots[] = { 2,0,0,2,2,2 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateRowLeft) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateRowLeft(slice);
  }

  // rotateCubeLeft() test repeated here

  Cubelet::color_t sides[] = { 'R','B','G','W','Y','O' };
  int rots[] = { 0,1,3,0,0,0 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateRowRight) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateRowRight(slice);
  }

  // rotateCubeRight() test repeated here

  Cubelet::color_t sides[] = { 'O','B','G','Y','W','R' };
  int rots[] = { 0,3,1,0,0,0 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateRowTwice) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateRowTwice(slice);
  }

  // rotateCubeLeft2() test repeated here

  Cubelet::color_t sides[] = { 'Y','B','G','R','O','W' };
  int rots[] = { 0,2,2,0,0,0 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateSliceCW) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateSliceCW(slice);
  }

  // rotateCubeSpinCW() test repeated here

  Cubelet::color_t sides[] = { 'W','O','R','G','B','Y' };
  int rots[] = { 1,1,1,1,1,3 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateSliceCCW) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateSliceCCW(slice);
  }

  // rotateCubeSpinCCW() test repeated here

  Cubelet::color_t sides[] = { 'W','R','O','B','G','Y' };
  int rots[] = { 3,3,3,3,3,1 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}

TEST(RotateSliceTests, rotateSliceTwice) {
	Cube cube(CUBE_SIZE);

  for (int slice = CUBE_SIZE; slice--;) {
    cube.rotateSliceTwice(slice);
  }

  // rotateCubeSpin2() test repeated here

  Cubelet::color_t sides[] = { 'W','G','B','R','O','Y' };
  int rots[] = { 2,2,2,2,2,2 };

  for (int row = CUBE_SIZE; row--;) {
    EXPECT_TRUE(cube.getFace(row).isSolved(sides[row])) << "row=" << row;
    EXPECT_EQ(cube.getFace(row).faceRotation(), rots[row]) << "row=" << row;
    for (int col = CUBE_SIZE; col--;) {
      for (int side = 6; side--;) {
        EXPECT_EQ(cube.getFace(side).getC(row, col).rot, rots[side]) << "row=" << row << ",col=" << col << ",side=" << side;
        switch (rots[side]) {
        case 0:
          EXPECT_EQ(cube.getFace(side).getC(row, col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 1:
          EXPECT_EQ(cube.getFace(side).getC(col, CUBE_SIZE - 1 - row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 2:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - row, CUBE_SIZE - 1 - col).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        case 3:
          EXPECT_EQ(cube.getFace(side).getC(CUBE_SIZE - 1 - col, row).pos, row * CUBE_SIZE + col) << "row=" << row << ",col=" << col << ",side=" << side;
          break;
        }
      }
    }
  }
}
