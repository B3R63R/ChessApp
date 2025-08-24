#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui_whitepiececlasses.h"
#include "gui_blackpiececlasses.h"
#include "gui_moveindicator.h"
#include <QLayout>
#include <QDebug>
#include <QList>
#include <algorithm>
#include "gui_moveindicator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    board.setupPieces();
    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);
    ui->gridLayout->setSpacing(0);
    //reverseBoard();
    setAudioEffects();
    setupSquaresColors();
    setupSquaresParameters();
    setupLabelParameters();
    setupBoardBorder();
    setupPieces();
    //handleCheck();
    handleGameStatus();




}


MainWindow::~MainWindow()
{
    delete ui;
    delete gameData;
}

int convertColCharToIntIdx(char col) {
    return col - 'A';
}

char convertColIntToCharIdx(int col) {
    return col + 'A';
}

int convertRowCharToIntIdx(char row) {
    return row - 1 - '0';
}

char convertRowIntToCharIdx(int row) {
    return row + 1 + '0';
}

void MainWindow::setAudioEffects() {
    double volume = 0.2;
    aMoveSelf = new QSoundEffect(this);
    aMoveSelf->setSource(QUrl("qrc:/sounds/sounds/move-self.wav"));
    aMoveSelf->setVolume(volume);

    aMoveEnemy = new QSoundEffect(this);
    aMoveEnemy->setSource(QUrl("qrc:/sounds/sounds/move-enemy.wav"));
    aMoveEnemy->setVolume(volume);

    aGameEnd = new QSoundEffect(this);
    aGameEnd->setSource(QUrl("qrc:/sounds/sounds/game-end.wav"));
    aGameEnd->setVolume(volume);

    aCheck = new QSoundEffect(this);
    aCheck->setSource(QUrl("qrc:/sounds/sounds/move-check.wav"));
    aCheck->setVolume(volume);

    aCapture = new QSoundEffect(this);
    aCapture->setSource(QUrl("qrc:/sounds/sounds/capture.wav"));
    aCapture->setVolume(volume);

    aCastle = new QSoundEffect(this);
    aCastle->setSource(QUrl("qrc:/sounds/sounds/castle.wav"));
    aCastle->setVolume(volume);
}
void disconnectAllChildren(QObject *parent) {

    QList<QObject *> children = parent->findChildren<QObject *>();

    for (QObject *child : children) {
        child->disconnect();
    }
}

void MainWindow::swapGridWidgets(int row1, int col1, int row2, int col2) {

    auto item1 = ui->gridLayout->takeAt(ui->gridLayout->indexOf(ui->gridLayout->itemAtPosition(row1, col1)));
    auto item2 = ui->gridLayout->takeAt(ui->gridLayout->indexOf(ui->gridLayout->itemAtPosition(row2, col2)));

    ui->gridLayout->addItem(item1, row2, col2);
    ui->gridLayout->addItem(item2, row1, col1);
}

void MainWindow::reverseBoard() {

    int halfSize = BOARD_SIZE / 2;

    for (int row = 0; row < halfSize; row++) {
        for (int col = 1; col <= BOARD_SIZE; col++) {
            //skip first col for labels - (col = 1)
            //skip last row for labels - (size -1)
            swapGridWidgets(row, col, BOARD_SIZE -1 - row, BOARD_SIZE-col+1);
        }
    }

    //Change position labels
    for (int col = 0; col < halfSize; col++) {

        //Rows
        swapGridWidgets(col, 0, BOARD_SIZE - 1 - col, 0);

        //Columns
        swapGridWidgets(BOARD_SIZE, col+1, BOARD_SIZE, BOARD_SIZE - col);
    }

}

void MainWindow::handleGameStatus() {
    gameData = new GUI::GameData();
    connect(gameData, &GUI::GameData::moveMadeChanged, this, [=, this]() {

        //return {isEndgame, isCheckmate, isChecked, pieceColor, kingRow, kingCol};
        std::tuple<bool, bool, bool, LOGIC::Color, int, int> gameStatus = board.examineGameStatus();

        bool isEndgame = std::get<0>(gameStatus);
        bool isCheckmate = std::get<1>(gameStatus);
        bool isChecked = std::get<2>(gameStatus);
        //LOGIC::Color pieceColor = std::get<3>(gameStatus);


        //Handle endgame
        if (isEndgame) {
            disconnectAllChildren(ui->frame);
            //Play sound effect
            aGameEnd->play();
        }

        // handle check
        if (isChecked) {
            int kingRowInt = std::get<4>(gameStatus);
            int kingColInt = std::get<5>(gameStatus);
            char kingRowChar = convertRowIntToCharIdx(kingRowInt);
            char kingColChar = convertColIntToCharIdx(kingColInt);
            std::string kingSquareName = "frame_" + std::string(1, kingColChar) + std::string(1,kingRowChar);
            auto kingSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(kingSquareName));
            if (isCheckmate) {
                kingSquare->setStyleSheet("background-color: #8C1D18;");
            }
            else {
                kingSquare->setStyleSheet("background-color: #D4AF37;");
                //Play sound effect
                aCheck->play();
            }
            gameData->lastKingSquareName =kingSquareName;
        }
        else {
            if (!(gameData->lastKingSquareName.empty())) {
                auto kingSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(gameData->lastKingSquareName));

                int row = convertRowIntToCharIdx(gameData->lastKingSquareName[7]);
                int col = convertColCharToIntIdx(gameData->lastKingSquareName[6]);

                updateSquareColor(kingSquare, row, col);
                gameData->lastKingSquareName.clear();

            }
        }


    });

}

void MainWindow::clearIndicators() {
    QList<GUI::MoveIndicator*> indicators = findChildren<GUI::MoveIndicator*>();
    for (auto indicator : indicators) {
        indicator->deleteLater();
    }
}

bool MainWindow::handleTransferRookWhenCastling() {
    std::tuple<bool, char, int> castlingData = board.getIsCastling();
    if (std::get<0>(castlingData)) {

        char rowRookInt = std::get<2>(castlingData);
        int colRookInt = (std::get<1>(castlingData) == 'l') ? 0 : 7;
        int newColRookInt = (std::get<1>(castlingData) == 'l') ? 3 : 5;

        char rookRowChar = convertRowIntToCharIdx(rowRookInt);
        char rookColChar = convertColIntToCharIdx(colRookInt);
        char newRookColChar = convertColIntToCharIdx(newColRookInt);

        std::string rookSquareName = "frame_" + std::string(1, rookColChar) + std::string(1,rookRowChar);
        auto rookSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(rookSquareName));
        auto rook = rookSquare->findChild<GUI::Piece*>();
        std::string newRookSquareName = "frame_" + std::string(1, newRookColChar) + std::string(1,rookRowChar);
        auto newRookSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(newRookSquareName));

        rookSquare->layout()->removeWidget(rook);
        newRookSquare->layout()->addWidget(rook);
        rook->setCurrentFrame(newRookSquare);

        //Play sound effect
        aCastle->play();
        return true;
    }
    else return false;
}


void MainWindow::handleEmptySquareMove(int row, int col) {
    //Download available moves
    std::vector<std::tuple<int,int>> availableMovesStorage = board.RaisePiece(row, col);
    availableMovesHistory = availableMovesStorage;

    //Show new indicators
    for (auto& [row, col] : availableMovesStorage) {

        //Convert data types
        char rowChar = convertRowIntToCharIdx(row);
        char colChar = convertColIntToCharIdx(col);

        //Create full objectName
        std::string squareName = "frame_" + std::string(1, colChar) + std::string(1,rowChar);

        //Access frame by objectName
        auto targetSquare = ui->frame->findChild<QFrame*>(squareName);

        //Check if square is empty
        auto targetSquarePiece = targetSquare->findChild<GUI::Piece*>();

        if (targetSquarePiece) {
            continue;
        }

        //Load indicator
        GUI::MoveIndicator *mIndicator = new GUI::MoveIndicator(targetSquare);
        targetSquare->layout()->addWidget(mIndicator);  
        //targetSquare->layout()->setAlignment(mIndicator, Qt::AlignCenter);

        //handling move on empty square
        connect(mIndicator, &QPushButton::clicked, this, [=, this]() {

            //Clear indicators from board

            auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
            auto targetSquare = ui->frame->findChild<QFrame*>(QString::fromStdString(squareName));

            if (!lastPieceSquareClicked || !targetSquare) return;

            GUI::Piece* lastPiece = lastPieceSquareClicked->findChild<GUI::Piece*>();
            if (!lastPiece) return;

            //Raise piece from board
            lastPieceSquareClicked->layout()->removeWidget(lastPiece);

            //Place raised piece on new square
            targetSquare->layout()->addWidget(lastPiece);
            lastPiece->setCurrentFrame(targetSquare);

            //Play sound effect
            if (!handleEnPassant(row, col)) {
                if (lastPiece->getColor() == LOGIC::Color::WHITE) aMoveSelf->play();
                else aMoveEnemy->play();
            }

            clearIndicators();

            //Update logic program
            board.makeLegalMove(lastRowClicked, lastColClicked, row, col);
            board.display();
            gameData->setMoveMade();

            //Play sound effect
            if (!handleTransferRookWhenCastling()) {
                if (lastPiece->getColor() == LOGIC::Color::WHITE) aMoveSelf->play();
                else aMoveEnemy->play();
            }

            lastClickedPieceSquareName.clear();
            lastRowClicked = -1;
            lastColClicked = -1;
            availableMovesHistory.clear();
        });

    }

}

bool MainWindow::handleEnPassant(int row, int col) {
    bool wasEnPassant = std::get<0>(board.getEnPassantInfo());
    int enPassantTargetRow = std::get<1>(board.getEnPassantInfo());
    int enPassantTargetCol = std::get<2>(board.getEnPassantInfo());
    qDebug()<< wasEnPassant << enPassantTargetRow << enPassantTargetCol;

    if (!(wasEnPassant && enPassantTargetRow == row && enPassantTargetCol == col)) return false;

    int capturedPawnRow = std::get<3>(board.getEnPassantInfo());
    int capturedPawnCol = std::get<4>(board.getEnPassantInfo());


    char capturedRowChar = convertRowIntToCharIdx(capturedPawnRow);
    char capturedColChar = convertColIntToCharIdx(capturedPawnCol);

    //Create full objectName
    std::string capturedSquareName = "frame_" + std::string(1, capturedColChar) + std::string(1,capturedRowChar);

    auto capturedPawnSquare = ui->frame->findChild<QFrame*>(capturedSquareName);

    if (!capturedPawnSquare) return false;

    auto capturedPawnPiece = capturedPawnSquare->findChild<GUI::Piece*>();

    if (!capturedPawnPiece) return false;

    capturedPawnPiece->deleteLater();

    //Play sound effect
    aCapture->play();
    return true;
}

int MainWindow::handleCapture(int row, int col, std::string fieldName) {

    clearIndicators();

    auto lastPieceSquareClicked = ui->frame->findChild<QFrame*>(lastClickedPieceSquareName);
    auto currentPieceSquareClicked = ui->frame->findChild<QFrame*>(fieldName);
    auto lastPiece = lastPieceSquareClicked->findChild<GUI::Piece*>();

    if (!lastPiece) return 0;

    auto currentPiece = currentPieceSquareClicked->findChild<GUI::Piece*>();
    if (!lastPieceSquareClicked || !currentPieceSquareClicked) return 0;
    lastPieceSquareClicked->layout()->removeWidget(lastPiece);
    if (currentPiece) {
        //delete taken piece
        currentPieceSquareClicked->layout()->removeWidget(currentPiece);
        currentPiece->deleteLater();
    }
    //add piece to new square
    currentPieceSquareClicked->layout()->addWidget(lastPiece);
    lastPiece->setCurrentFrame(currentPieceSquareClicked);

    //play saund effect
    aCapture->play();

    //update logic program
    board.makeLegalMove(lastRowClicked, lastColClicked, row, col);

    gameData->setMoveMade();
    lastClickedPieceSquareName.clear();
    lastRowClicked = -1;
    lastColClicked = -1;

    return 0;
}


int MainWindow::handlePieceClick(const std::string& fieldName) {
    //Download coordinates
    int rowIdx = convertRowCharToIntIdx(fieldName[7]);
    int colIdx = convertColCharToIntIdx(fieldName[6]);
    std::tuple<int, int> move = {rowIdx, colIdx};
    const auto& piece = board.getBoard()[rowIdx][colIdx];

    //protection from nullptr
    if (!piece) return 0;

    //Check if it right color to move
    if ((piece->getColor() == LOGIC::Color::WHITE && !board.getIsWhiteTurn()) ||
        (piece->getColor() == LOGIC::Color::BLACK && board.getIsWhiteTurn())) {

        if (availableMovesHistory.empty()) {
            return 0;
            }
            //Beating
            else {
                if (std::find(availableMovesHistory.begin(), availableMovesHistory.end(), move) != availableMovesHistory.end()) {
                    handleCapture(rowIdx, colIdx, fieldName);
                    board.display();
                }
                return 0;
            }

    }
    //Clear previous indicators from board
    clearIndicators();

    //Set variables to store last click history
    lastClickedPieceSquareName = fieldName;
    lastRowClicked = rowIdx;
    lastColClicked = colIdx;

    handleEmptySquareMove(rowIdx, colIdx);

    return 0;

}

void MainWindow::setPiece(QFrame *frame, GUI::Piece *piece) {

    frame->layout()->addWidget(piece);
    piece->setCurrentFrame(frame);
    connect(piece, &QPushButton::clicked, this, [=, this]() {

        handlePieceClick(piece->getCurrentFrame()->objectName().toStdString());

    });
}

GUI::Piece* MainWindow::choosePiece(LOGIC::Color color, LOGIC::PieceType pieceType, QFrame *frame) {
    if (color == LOGIC::Color::WHITE) {
        switch (pieceType) {
        case LOGIC::PieceType::ROOK:   return new GUI::RookWhite(color, frame);
        case LOGIC::PieceType::KNIGHT: return new GUI::KnightWhite(color, frame);
        case LOGIC::PieceType::BISHOP: return new GUI::BishopWhite(color, frame);
        case LOGIC::PieceType::QUEEN:  return new GUI::QueenWhite(color, frame);
        case LOGIC::PieceType::KING:   return new GUI::KingWhite(color, frame);
        case LOGIC::PieceType::PAWN:   return new GUI::PawnWhite(color, frame);
        }
    } else { // BLACK
        switch (pieceType) {
        case LOGIC::PieceType::ROOK:    return new GUI::RookBlack(color, frame);
        case LOGIC::PieceType::KNIGHT:  return new GUI::KnightBlack(color, frame);
        case LOGIC::PieceType::BISHOP:  return new GUI::BishopBlack(color, frame);
        case LOGIC::PieceType::QUEEN:   return new GUI::QueenBlack(color, frame);
        case LOGIC::PieceType::KING:    return new GUI::KingBlack(color, frame);
        case LOGIC::PieceType::PAWN:    return new GUI::PawnBlack(color, frame);
        }
    }
    return nullptr;
};

void MainWindow::setupPieces() {

    QMap<char, LOGIC::PieceType> piecesMap;
    //Key-column symbol, value-piece symbol
    //Craated for custom piece location;
    piecesMap['A'] = LOGIC::PieceType::ROOK;  piecesMap['H'] = LOGIC::PieceType::ROOK;
    piecesMap['B'] = LOGIC::PieceType::KNIGHT;  piecesMap['G'] = LOGIC::PieceType::KNIGHT;
    piecesMap['C'] = LOGIC::PieceType::BISHOP;  piecesMap['F'] = LOGIC::PieceType::BISHOP;
    piecesMap['D'] = LOGIC::PieceType::QUEEN;  piecesMap['E'] = LOGIC::PieceType::KING;

    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();

    for (auto *frame : SquaresStorage) {
        auto fieldName = frame->objectName().toStdString();
        char row = fieldName[7];
        char col = fieldName[6];
        LOGIC::Color color;
        LOGIC::PieceType pieceType;
        bool shouldCreatePiece = false;

        if (!fieldName.starts_with("frame_")) continue;

        //Pawns
        if (row == '2' || row == '7') {
            color = (row == '2') ? LOGIC::Color::WHITE : LOGIC::Color::BLACK;
            pieceType = LOGIC::PieceType::PAWN;
            shouldCreatePiece = true;

        }
        //Other pieces
        else if (row == '1' || row == '8') {
            color = (row == '1') ? LOGIC::Color::WHITE : LOGIC::Color::BLACK;
            pieceType = piecesMap[col];
            shouldCreatePiece = true;

        }

        if (shouldCreatePiece) {
            auto piece = choosePiece(color, pieceType, frame);
            setPiece(frame, piece);
        }
    }

}



void MainWindow::setupLabelParameters() {
    QList<QLabel*> labelsStorage = ui->frame->findChildren<QLabel*>();
    for (auto label : labelsStorage) {
        //label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(
                "font-family: 'CARDOT';"
                "font-size: 15pt;"
            "color: #EAEAEA;"
            "background-color: #151515;"   );

    }

}

void MainWindow::setupBoardBorder() {
    ui->frame->setStyleSheet("#frame {padding-top: 0.5; border: none;}");

    QString borderStyle = "1.5px solid #7f7f7f;";
    QList<QWidget*> widgetStorage = ui->frame->findChildren<QWidget*>();
    for (auto widget : widgetStorage) {

        int widgetIdx = ui->gridLayout->indexOf(widget);
        QString currentStyle = widget->styleSheet();
        QString style;
        if (widgetIdx == -1) continue;
        int row, col, _;
        ui->gridLayout->getItemPosition(widgetIdx,  &row, &col, &_, &_);

        //Left side
        if (col == 1 && row != BOARD_SIZE) {
            style += "border-left: " + borderStyle;

        }
        //Right side
        if (col == BOARD_SIZE && row !=BOARD_SIZE) style += "border-right: " + borderStyle;


        if (row == BOARD_SIZE-1) {
            if (col != 0) style += "border-bottom: " + borderStyle;
        }

        //Top side
        if (row == 0 && col != 0) style += "border-top: " + borderStyle;

        //Set style
        if (!style.isEmpty()) widget->setStyleSheet(currentStyle + style + "border-style: solid;");


    }

}

void MainWindow::setupSquaresParameters() {

    QList<QFrame*> SquaresStorage = ui->frame->findChildren<QFrame*>();
    for (auto frame : SquaresStorage) {
        if (!frame->objectName().startsWith("frame_")) continue;
        if (!frame->layout()) {
            auto layout = new QVBoxLayout(frame);
            frame->setLayout(layout);
        }

    }


}

void MainWindow::updateSquareColor(QFrame* square, int row, int col)
{
    const QString whiteSquareColor = "background-color: #3d3d3d; border: none;";
    const QString blackSquareColor = "background-color: #7f7f7f; border: none;";
    //ASCII 'A' numerical value is 65.
    if ((row % 2) == (col % 2)) {
        square->setStyleSheet(blackSquareColor);
    } else {
        square->setStyleSheet(whiteSquareColor);
    }
}

void MainWindow::setupSquaresColors() {
    QList<QFrame*> chessSquaresList = ui->frame->findChildren<QFrame*>();
    for (auto frame : chessSquaresList) {
        QString frameName= frame->objectName();

        int col = int(frameName.toStdString()[6]);
        int row = int(frameName.toStdString()[7]);

        updateSquareColor(frame, row, col);
    }
}

