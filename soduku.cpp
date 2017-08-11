#include <QtWidgets>

#include "soduku.h"

Soduku::Soduku(QWidget *parent)
    : QWidget(parent)
{

    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QPoint te(300, 1);
    this->move(te);
    createMenuScreen();


    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

}

Soduku::~Soduku()
{

}

void Soduku::generateSoduku() {



    delete startSolverBtn;
    delete aboutBtn;
    delete exitBtn;
    delete generateBtn;
    delete title;
    delete verticalLayout;

    setFixedHeight(250);

    level = new QVBoxLayout;


    level->addWidget(easyBtn = new QPushButton("Easy", this));
    easyBtn->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    easyBtn->setFocusPolicy(Qt::NoFocus);

    level->addWidget(moderateBtn = new QPushButton("Moderate", this));
    moderateBtn->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    moderateBtn->setFocusPolicy(Qt::NoFocus);

    level->addWidget(hardBtn = new QPushButton("Hard", this));
    hardBtn->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    hardBtn->setFocusPolicy(Qt::NoFocus);

    signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(easyBtn, QString("Easy"));
    signalMapper->setMapping(moderateBtn, QString("Moderate"));
    signalMapper->setMapping(hardBtn, QString("Hard"));

    connect(easyBtn, SIGNAL(clicked()),
        signalMapper, SLOT (map()));
    connect(moderateBtn, SIGNAL(clicked()),
            signalMapper, SLOT (map()));
    connect(hardBtn,SIGNAL(clicked()),
            signalMapper, SLOT (map()));

    connect(signalMapper, SIGNAL(mapped(QString)),
        this, SLOT(generation(QString)));

    setLayout(level);


}

int Soduku::randInt(int low, int high) {
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low; /*formula for creating random numbers
                                                   generating soduko puzzle*/
}

void Soduku::showAns() {
    for(int i= 0; i < NUM; i++) {
        for(int j = 0; j < NUM; j++) {

                cells[i][j]->setText(QString::number(grid[i][j]));



        }
    }
}


void Soduku::regenerate() {
    QFont cellFont("Courier New");
    cellFont.setPointSize(30);


    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            delete cells[i][j];
        }

    }


    // int tGrid[9][9];
    for(int i= 0; i < NUM; i++) {
        for(int j = 0; j < NUM; j++) {
                grid[i][j] = 0;
        }
    }

    int randRow, randCol, randNum;

    randRow = randInt(1,9);
    randCol = randInt(1,9);
    randNum = randInt(1,9);
    grid[randRow][randCol]  = randNum;




    // line edit box for 9 * 9 grid
    int startingRow = 6;
    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            cells[i][j] = new QLineEdit;
            cells[i][j]->setFixedSize(45,45);
            cells[i][j]->setStyleSheet("QLineEdit{background: transparent; border: none;} QLineEdit:hover{border: 1px solid gray; background-color:  #1E90FF;}");
            cells[i][j]->setFont(cellFont);
             cells[i][j]->setMaxLength(1);

            cells[i][j]->setValidator( new QIntValidator(0, 9, this) );

            cells[i][j]->setAlignment(Qt::AlignCenter);
            mLayout->addWidget(cells[i][j], startingRow,j);
        }

        startingRow++;
    }


int maxHiddenCellCount;

if(currentLevel == "Easy")
    maxHiddenCellCount = randInt(1,30);
else if(currentLevel == "Moderate")
    maxHiddenCellCount = randInt(31,50);
else if(currentLevel == "Hard")
    maxHiddenCellCount = randInt(51,80);

    QList<int> hiddenCell;
        for(int i= 0; i < maxHiddenCellCount; i++) {
           hiddenCell.append(randInt(1,81));
        }



int s = 0;
bool change = false;
    if (SolveSudoku(grid) == true) {
        for(int i= 0; i < NUM; i++) {
            for(int j = 0; j < NUM; j++) {
                s++;
                if( hiddenCell.indexOf(s) != -1 ) {

                    cells[i][j]->setText("");
                }
                else {
                    qDebug() << s;
                    cells[i][j]->setText(QString::number(grid[i][j]));
                }


            }
        }
    }



}
void Soduku::generation(QString lev) {


    delete hardBtn;
    delete easyBtn;
    delete moderateBtn;
    delete level;

    setFixedHeight(650);
currentLevel = lev;

    qDebug() << "sd" << lev << randInt(0,100);




    QFont cellFont("Courier New");
    cellFont.setPointSize(30);


    title = new QLabel;
    title->setText("Fill up your soduku problem in the following grid. <hr />");
    title->setStyleSheet("font-size:15px;background:none;");
    // create layout for the main game

    mLayout = new QGridLayout;
    // add title to the grid
    mLayout->addWidget(title, 0, 0,2,9);

    // int tGrid[9][9];
    for(int i= 0; i < NUM; i++) {
        for(int j = 0; j < NUM; j++) {
                grid[i][j] = 0;
        }
    }

    int randRow, randCol, randNum;

    randRow = randInt(1,9);
    randCol = randInt(1,9);
    randNum = randInt(1,9);
    grid[randRow][randCol]  = randNum;




    // line edit box for 9 * 9 grid
    int startingRow = 6;
    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            cells[i][j] = new QLineEdit;
            cells[i][j]->setFixedSize(45,45);
            cells[i][j]->setStyleSheet("QLineEdit{background: transparent; border: none;} QLineEdit:hover{border: 1px solid gray; background-color:  #1E90FF;}");
            cells[i][j]->setFont(cellFont);
             cells[i][j]->setMaxLength(1);

            cells[i][j]->setValidator( new QIntValidator(0, 9, this) );

            cells[i][j]->setAlignment(Qt::AlignCenter);
            mLayout->addWidget(cells[i][j], startingRow,j);
        }

        startingRow++;
    }


int maxHiddenCellCount;

if(lev == "Easy")
    maxHiddenCellCount = randInt(1,30);
else if(lev == "Moderate")
    maxHiddenCellCount = randInt(31,50);
else if(lev == "Hard")
    maxHiddenCellCount = randInt(51,80);

    QList<int> hiddenCell;
        for(int i= 0; i < maxHiddenCellCount; i++) {
           hiddenCell.append(randInt(1,81));
        }



int s = 0;
bool change = false;
    if (SolveSudoku(grid) == true) {
        for(int i= 0; i < NUM; i++) {
            for(int j = 0; j < NUM; j++) {
                s++;
                if( hiddenCell.indexOf(s) != -1 ) {

                    cells[i][j]->setText("");
                }
                else {
                    qDebug() << s;
                    cells[i][j]->setText(QString::number(grid[i][j]));
                }


            }
        }
    }

    int rCount = startingRow;

    complexity = new QLabel("Complexity " + lev, this);
    complexity->setStyleSheet("border: 2px solid black;font-size: 15px;padding: 5px; margin-top: 20px");
    mLayout->addWidget(complexity, rCount += 10, 0, rCount, 9);


    mLayout->addWidget(showAnswer = new QPushButton("Show Answer", this), startingRow + 35, 0,  startingRow + 4, 9);
    showAnswer->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");
    showAnswer->setFocusPolicy(Qt::NoFocus);


    mLayout->addWidget(generateNew = new QPushButton("Generate New", this), startingRow +53, 0,  startingRow + 28, 9);
    generateNew->setStyleSheet("padding: 10px 35px 10px 35px;borderline:red;font-size: 25px; font-family: Courier, Arial;margin-top: 10px;");
    generateNew->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    generateNew->setFocusPolicy(Qt::NoFocus);


    mLayout->addWidget(menuBtn = new QPushButton("Back to Menu", this), startingRow + 94, 0,  startingRow + 30 , 9);
    menuBtn->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    menuBtn->setFocusPolicy(Qt::NoFocus);

    connect(showAnswer, SIGNAL (released()), this, SLOT (showAns()));
    connect(generateNew, SIGNAL (released()), this, SLOT (regenerate()));

    connect(menuBtn, SIGNAL (released()), this, SLOT (deleteGenerateScreen()));

    setLayout(mLayout);
     palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap("C:/Users/User/Desktop/grid.jpg")))));
    setPalette(*palette);

}

void Soduku::createGameScreen() {





    delete startSolverBtn;
    delete aboutBtn;
    delete exitBtn;
    delete generateBtn;
    delete title;
    delete verticalLayout;

    setFixedHeight(650);


    QFont cellFont("Courier New");
    cellFont.setPointSize(30);


    title = new QLabel;
    title->setText("Fill up your soduku problem in the following grid. <hr />");
    title->setStyleSheet("font-size:15px;background:none;");
    // create layout for the main game

    mLayout = new QGridLayout;
    // add title to the grid
    mLayout->addWidget(title, 0, 0,2,9);

    // line edit box for 9 * 9 grid
    int startingRow = 6;
    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            cells[i][j] = new QLineEdit;
            cells[i][j]->setFixedSize(45,45);
            cells[i][j]->setStyleSheet("QLineEdit{background: transparent; border: none;} QLineEdit:hover{border: 1px solid gray; background-color:  #1E90FF;}");
            cells[i][j]->setFont(cellFont);
             cells[i][j]->setMaxLength(1);

            cells[i][j]->setValidator( new QIntValidator(0, 9, this) );

            cells[i][j]->setAlignment(Qt::AlignCenter);
            mLayout->addWidget(cells[i][j], startingRow,j);
        }

        startingRow++;
    }


    int rCount = startingRow;

    complexity = new QLabel("Complexity", this);
    complexity->setStyleSheet("border: 2px solid black;font-size: 15px;padding: 5px; margin-top: 20px");
    mLayout->addWidget(complexity, rCount += 10, 0, rCount, 9);


    mLayout->addWidget(solveButton = new QPushButton("Solve Soduku", this), startingRow + 35, 0,  startingRow + 4, 9);
    solveButton->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");
    solveButton->setFocusPolicy(Qt::NoFocus);


    mLayout->addWidget(resetButton = new QPushButton("Reset Grid", this), startingRow +53, 0,  startingRow + 28, 9);
    // resetButton->setStyleSheet("padding: 10px 35px 10px 35px;borderline:red;font-size: 25px; font-family: Courier, Arial;margin-top: 10px;");
    resetButton->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    resetButton->setFocusPolicy(Qt::NoFocus);


    mLayout->addWidget(menuBtn = new QPushButton("Back to Menu", this), startingRow + 94, 0,  startingRow + 30 , 9);
    menuBtn->setStyleSheet("padding: 10px 15px 10px 15px; font-size: 20px; font-family: Courier, Arial;margin-top: 10px;");

    menuBtn->setFocusPolicy(Qt::NoFocus);

    connect(solveButton, SIGNAL (released()), this, SLOT (solveSoduku()));
    connect(resetButton, SIGNAL (released()), this, SLOT (resetSoduku()));

    connect(menuBtn, SIGNAL (released()), this, SLOT (backMenu()));

    setLayout(mLayout);
     palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap("C:/Users/User/Desktop/grid.jpg")))));
    setPalette(*palette);
}

void Soduku::deleteGenerateScreen() {

    delete title;
    delete mLayout;
    delete complexity;
    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            delete cells[i][j];

        }

     }




    delete generateNew ;


    delete showAnswer ;
    delete menuBtn ;




    delete palette;

    palette = new QPalette();
   palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap("C:/Users/san/Desktop/blank.jpg")))));
   setPalette(*palette);
    createMenuScreen();

}


void Soduku::deleteGameScreen() {

    delete title;
    delete mLayout;
    delete complexity;
    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            delete cells[i][j];

        }

     }




    delete solveButton ;


    delete resetButton ;
    delete menuBtn ;




    delete palette;

}



void Soduku::backMenu() {

    deleteGameScreen();

    setFixedHeight(400);
    setFixedWidth(500);

    palette = new QPalette();
   palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap("C:/Users/san/Desktop/blank.jpg")))));
   setPalette(*palette);

    createMenuScreen();

}


void Soduku::resetSoduku() {
    complexity->setText("complexity ");
    /*
    for(int i= 0; i < NUM; i++) {
        for(int j = 0; j < NUM; j++) {
           cells[i][j]->setText("");
        }
    }

    solveButton->setText("Solve again");

*/
    for(int i = 0; i < NUM; i++) {


        for(int j = 0; j < NUM; j++) {
            cells[i][j]->setText("");
            cells[i][j]->setStyleSheet("QLineEdit{background: transparent; border: none;} QLineEdit:hover{border: 1px solid gray; background-color:  #1E90FF;}");

        }

     }

}

// show main menu at the start of the game
void Soduku::createMenuScreen() {


    setFixedHeight(450);
    setFixedWidth(500);

    verticalLayout = new QVBoxLayout(this);


    title = new QLabel(this);


    title->setStyleSheet("background-image:url('C:/Users/User/Desktop/logo.png'); background-repeat: no-repeat;background-position: 100px 50px;");


    startSolverBtn = new QPushButton("Start", this);
    generateBtn = new QPushButton("Generate Soduku", this);
    aboutBtn = new QPushButton("About", this);
    exitBtn = new QPushButton("Exit", this);


    verticalLayout->addWidget(title);
    verticalLayout->addWidget(startSolverBtn);
    verticalLayout->addWidget(generateBtn);

    verticalLayout->addWidget(aboutBtn);
    verticalLayout->addWidget(exitBtn);

    connect(startSolverBtn, SIGNAL(clicked()), this, SLOT(createGameScreen()));

    connect(aboutBtn, SIGNAL(clicked()), this, SLOT(aboutDialog()));
    connect(generateBtn, SIGNAL(clicked()), this, SLOT(generateSoduku()));

    connect(exitBtn, SIGNAL(clicked()), this, SLOT(close()));


    setLayout(verticalLayout);
}




void Soduku::aboutDialog()
{
    // QMessageBox::StandardButton reply;
    QMessageBox about;
    about.setWindowTitle("About Sudoku Solver");

    about.setText("<div style='font-size: 30px;'>Soduku Solver </div> <hr /> <br /> <div style='font-size: 16px;'>Lorem ipsum dolor sit amet, "
                  "consectetur adipiscing elit. Vivamus accumsan leo ante. Etiam "
                  "accumsan a magna at rhoncus. Nullam et varius arcu, ut feugiat tellus. "
                  "Nunc sed orci non mi vulputate malesuada nec vel nibh. Praesent at elit "
                  "velit. Nullam interdum, ipsum id ullamcorper mollis, purus nisi "
                  "fermentum elit, cursus faucibus magna ipsum ut ante. Mauris fringilla, "
                  "dolor quis laoreet tincidunt, justo mauris lacinia ex, semper facilisis "
                  "turpis purus id eros. Sed non enim sed odio eleifend tempus nec eget "
                  "urna. Donec lorem diam, commodo eu enim quis, sagittis maximus sapien. "
                  "Suspendisse potenti. </div> ");

    about.exec();
}

void Soduku::solveSoduku()
{
    solveButton->setText("Initiate Solving . . .");
    solveButton->setEnabled(false);
    bool sol = true;
    int cs = 0;

    for(int i= 0; i < NUM; i++) {
        for(int j = 0; j < NUM; j++) {
            if(cells[i][j]->text().isEmpty() || cells[i][j]->text() == "")  {
               // qDebug() << "Empty";
                cs++;
            }
        }
    }

    if(cs == 81) {
        solveButton->setText("Invalid Problem!Solve again.");
        solveButton->setEnabled(true);
        sol = false;
        return;
    }

    int enteredCell = 0;

    for(int i= 0; i < NUM; i++) {
        for(int j = 0; j < NUM; j++) {
            if(cells[i][j]->text().isEmpty() || cells[i][j]->text() == "")  {
                // qDebug() << "as";
                grid[i][j] = 0;
                cells[i][j]->setStyleSheet("color:#1E90FF;border:none;background:transparent;");
            }
             else {
                enteredCell++;
                qDebug() << "new val = " << cells[i][j]->text().toInt();
                grid[i][j] = cells[i][j]->text().toInt();


            }

            qDebug() << grid[i][j];


        }

        qDebug() << "\n";
    }

    qDebug() << "Cell entered " <<enteredCell ;


   if(enteredCell >= 1 && enteredCell <= 30) {
       complexity->setText("Complexity Hard");
   }
   else if(enteredCell >= 31 && enteredCell <= 60) {
       complexity->setText("Complexity Moderate");

   }
   else if(enteredCell >= 61) {
       complexity->setText("Complexity Easy");

   }


 /*  for(int i= 0; i < NUM; i++) {
       for(int j = 0; j < NUM; j++) {
           if (cells[i][j]->text().toInt() != 0) {
                if(!isSafe(grid, i, j, cells[i][j]->text().toInt()))
                    return true;


               }
       }
   }


*/
    if (SolveSudoku(grid) == true && sol == true) {
        for(int i= 0; i < NUM; i++) {
            for(int j = 0; j < NUM; j++) {
                cells[i][j]->setText(QString::number(grid[i][j]));
            }
        }

        solveButton->setText("Solve Sudoku");
        solveButton->setEnabled(true);

    }
       else
            solveButton->setText("No Solution! Solve again");
}



/* Takes a partially filled-in grid and attempts to assign values to
  all unassigned locations in such a way to meet the requirements
  for Sudoku solution (non-duplication across rows, columns, and boxes) */
bool Soduku::SolveSudoku(int grid[NUM][NUM])
{
    int row, col;

    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(grid, row, col))
       return true; // success!

    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // if looks promising
        if (isSafe(grid, row, col, num))
        {
            // make tentative assignment
            grid[row][col] = num;

            // return, if success, yay!
            if (SolveSudoku(grid))
                return true;

            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}

/* Searches the grid to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
bool Soduku::FindUnassignedLocation(int grid[NUM][NUM], int &row, int &col)
{
    for (row = 0; row < NUM; row++)
        for (col = 0; col < NUM; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

/* Returns a boolean which indicates whether any assigned entry
   in the specified row matches the given number. */
bool Soduku::UsedInRow(int grid[NUM][NUM], int row, int num)
{
    for (int col = 0; col < NUM; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether any assigned entry
   in the specified column matches the given number. */
bool Soduku::UsedInCol(int grid[NUM][NUM], int col, int num)
{
    for (int row = 0; row < NUM; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether any assigned entry
   within the specified 3x3 box matches the given number. */
bool Soduku::UsedInBox(int grid[NUM][NUM], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
bool Soduku::isSafe(int grid[NUM][NUM], int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}

