// rabbits.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 25;               // max number of columns in the arena
const int MAXRABBITS = 100;           // max number of rabbits allowed

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NUMDIRS = 4;

const int EMPTY = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
    public:
        // Constructor
        Rabbit(Arena* ap, int r, int c);

        // Accessors
        int  row() const;
        int  col() const;
        bool isDead() const;

        // Mutators
        void move();

    private:
        Arena* m_arena;
        int    m_row;
        int    m_col;
        bool m_ispoisoned = false;
        int m_turnsPoisoned = 0;
        bool m_dead = false;
    
};

class Player
{
    public:
        // Constructor
        Player(Arena* ap, int r, int c);

        // Accessors
        int  row() const;
        int  col() const;
        bool isDead() const;

        // Mutators
        string dropPoisonedCarrot();
        string move(int dir);
        void   setDead();

    private:
        Arena* m_arena;
        int    m_row;
        int    m_col;
        bool   m_dead;
};

class Arena
{
    public:
        // Constructor/destructor
        Arena(int nRows, int nCols);
        ~Arena();

        // Accessors
        int     rows() const;
        int     cols() const;
        Player* player() const;
        int     rabbitCount() const;
        int     getCellStatus(int r, int c) const;
        int     numberOfRabbitsAt(int r, int c) const;
        void    display(string msg) const;

        // Mutators
        void setCellStatus(int r, int c, int status);
        bool addRabbit(int r, int c);
        bool addPlayer(int r, int c);
        void moveRabbits();

    private:
        int     m_grid[MAXROWS][MAXCOLS];
        int     m_rows;
        int     m_cols;
        Player* m_player;
        Rabbit* m_rabbits[MAXRABBITS];
        int     m_nRabbits; //1 more than the array index. [m_nRabbits-1] to access
        int     m_turns;

        // Helper functions
        void checkPos(int r, int c, string functionName) const;
        bool isPosInBounds(int r, int c) const;
};

class Game
{
    public:
        // Constructor/destructor
        Game(int rows, int cols, int nRabbits);
        ~Game();

        // Mutators
        void play();

    private:
        Arena* m_arena;

        // Helper functions
        string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
int checkAdjecent(const Arena& a, int r, int c);
bool rNorth(const Arena& a, int r, int c);
bool rEast(const Arena& a, int r, int c);
bool rSouth(const Arena& a, int r, int c);
bool rWest(const Arena& a, int r, int c);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();


///////////////////////////////////////////////////////////////////////////
//  Rabbit implementation
///////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{ 
    return m_col;  
}

bool Rabbit::isDead() const
{
    
    return m_dead;  
}

void Rabbit::move()
{
  
    int direction = randInt(NORTH, WEST);
    
    if (m_ispoisoned == true)
    {
        m_turnsPoisoned++;
        if (m_turnsPoisoned % 2 != 0)
        {
            
            return;
        }
    }

    attemptMove(*m_arena, direction, m_row, m_col);

    int stat = m_arena->getCellStatus(m_row, m_col);

    if (stat == HAS_POISON)
    {
        if (m_ispoisoned == true)
        {
            m_dead = true;
        }
        m_arena->setCellStatus(m_row, m_col, EMPTY);
        m_ispoisoned = true;
    }




    
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{ 
    return m_col; 
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
    
    if (!(attemptMove(*m_arena, dir, m_row, m_col)))
    {
        return "Player couldn't move; player stands.";
    }
    else if (m_arena->numberOfRabbitsAt(m_row, m_col) != 0)
    {
        setDead();
        return "Player walked into a rabbit and died.";
    }



    string direction = "";
    if (dir == 0)
    {
        direction = "north";
    }
    else if (dir == 1)
    {
        direction = "east";
    }
    else if (dir == 2)
    {
        direction = "south";
    }
    else if (dir == 3)
    {
        direction = "west";
    }
    
    
     return "Player moved " + direction + ".";
    

    
}

bool Player::isDead() const
{
    
    return m_dead;  
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    delete m_player;

    for (int i = 0; i < m_nRabbits; i++)
    {
        delete m_rabbits[i];
    }
   
}

int Arena::rows() const
{
    return m_rows; 
}

int Arena::cols() const
{
    return m_cols; 
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{ 
    return m_nRabbits;  
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r - 1][c - 1];
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
    int rab = 0;

    for (int i = 0; i < rabbitCount(); i++)
    {
        if ((m_rabbits[i]->row() == r) && (m_rabbits[i]->col() == c))
        {
            rab++;
        }
    }

    return rab;  
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r - 1][c - 1] = (getCellStatus(r, c) == EMPTY ? '.' : '*');

    // Indicate each rabbit's position
    for (int i = 0; i < rows(); i++)
    {
        for (int j = 0; j < cols(); j++)
        {
            int amnt = numberOfRabbitsAt(i+1,j+1);
            
          
            if (amnt > 1 && amnt < 9)
            {
                displayGrid[i][j] = amnt + '0';
            }
            else if (amnt > 8)
            {
                displayGrid[i][j] = 9 + '0';
            }
            else if (amnt == 1)
            {
                displayGrid[i][j] = 'R';
            }
        }
    }
    // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row() - 1][m_player->col() - 1] = (m_player->isDead() ? 'X' : '@');

    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;

    // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r - 1][c - 1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

    // Don't add a rabbit on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return false;

   
    if (m_nRabbits >= MAXRABBITS)
    {
        return false;
    }

    m_rabbits[m_nRabbits] = new Rabbit(this, r, c);
    m_nRabbits++;
   
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
    // Move all rabbits
    // TODO:  Move each rabbit.  Mark the player as dead if necessary.
    //        Deallocate any dead dynamically allocated rabbit.
    for (int i = 0; i < m_nRabbits; i++)
    {
        m_rabbits[i]->move();
        if (m_rabbits[i]->row() == m_player->row() && m_rabbits[i]->col() == m_player->col())
        {
            m_player->setDead();
        }
        else if (m_rabbits[i]->isDead())
        {
            delete m_rabbits[i];

            for (int j = i; j < m_nRabbits - 1; j++)
            {
                m_rabbits[j] = m_rabbits[j + 1];
            }
            m_nRabbits--;
        }

    }

    // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
            << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
            << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
            << cols << " arena, which is too small too hold a player and "
            << nRabbits << " rabbits!" << endl;
        exit(1);
    }

    // Create arena
    m_arena = new Arena(rows, cols);

    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

    // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
    default:  return false;
    case 'n': dir = NORTH; break;
    case 'e': dir = EAST;  break;
    case 's': dir = SOUTH; break;
    case 'w': dir = WEST;  break;
    }
    return true;
}


bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
   
    if (r == 1 && c == a.cols() && (dir ==0 || dir == 1)) //currently top right
    {
        return false;
    }
    else if (r == 1 && c == 1 && (dir == 3 || dir == 0)) //currently top left
    {
        return false;
    }
    else if (r == a.rows() && c == 1 && (dir == 2 || dir == 3)) //currently bot left
    {
        return false;
    }
    else if (r == a.rows() && c == a.cols() && (dir == 2 || dir == 1)) //current bot right
    {
        return false;
    }
    else if ((r == 1) && (dir == 0)) //top row
    {
        return false;
    }
    else if ((r == a.rows()) && (dir == 2)) //bot row
    {
        return false;
    }
    else if (c == 1 && dir == 3) //left col
    {
        return false;
    }
    else if (c == a.cols() && (dir == 1))
    {
        return false;
    }

    if (dir == NORTH)
    {
        r = r-1;
        return true;
    }
    else if (dir == EAST)
    {
        c = c+1 ;
        return true;
    }
    else if (dir == SOUTH)
    {
        r = r+1 ;
        return true;
    }
    else if (dir == WEST)
    {
        c = c -1;
        return true;
    }
 
    return true;  
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned carrot and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
int checkAdjecent(const Arena& a, int r, int c)
{
    int nRabbits = 0;
    if (r == 1 && c == 1) //top left
    {
        if (a.numberOfRabbitsAt(r + 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c + 1) != 0)
        {
            nRabbits++;
        }
    }
    else if (r == 1 && c == a.cols()) //top right
    {
        if (a.numberOfRabbitsAt(r + 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c - 1) != 0)
        {
            nRabbits++;
        }
    }
    else if (r == a.rows() && c == a.cols()) //bot right
    {
        if (a.numberOfRabbitsAt(r -1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c - 1) != 0)
        {
            nRabbits++;
        }
    }
    else if (r == a.rows() && c == 1) //bot left
    {
        if (a.numberOfRabbitsAt(r - 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c + 1) != 0)
        {
            nRabbits++;
        }
    }
    else if (r == 1) //top mid
    {
        if (a.numberOfRabbitsAt(r + 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c + 1) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c - 1) != 0)
        {
            nRabbits++;
        }
    }
    else if (r == a.rows()) //bot mid
    {
        if (a.numberOfRabbitsAt(r - 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c + 1) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c - 1) != 0)
        {
            nRabbits++;
        }
    }
    else if (c == 1) //left mid
    {
        if (a.numberOfRabbitsAt(r, c + 1) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r-1, c ) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r+1, c) != 0)
        {
            nRabbits++;
        }
    }
    else if (c == a.cols()) //right mid
    {
        if (a.numberOfRabbitsAt(r, c -1) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r - 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r + 1, c) != 0)
        {
            nRabbits++;
        }
    }
    else if (c < 1 || c> a.cols() || r < 1 || r> a.rows()) //invalid position
    {
        nRabbits = 100000;
    }
    else //middle piece
    {
        if (a.numberOfRabbitsAt(r, c - 1) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r - 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r + 1, c) != 0)
        {
            nRabbits++;
        }
        if (a.numberOfRabbitsAt(r, c+1) != 0)
        {
            nRabbits++;
        }
    }

    return nRabbits;
}
bool rNorth(const Arena& a, int r, int c)
{
    if (r == 1)
    {
        return true;
    }
    else
    {
        if (a.numberOfRabbitsAt(r - 1, c) != 0)
        {
            return true;
        }
    }
    return false;
}
bool rSouth(const Arena& a, int r, int c)
{
    if (r == a.rows())
    {
        return true;
    }
    else
    {
        if (a.numberOfRabbitsAt(r + 1, c) != 0)
        {
            return true;
        }
    }
    return false;
}
bool rEast(const Arena& a, int r, int c)
{
    if (c == a.cols())
    {
        return true;
    }
    else
    {
        if (a.numberOfRabbitsAt(r, c+1) != 0)
        {
            return true;
        }
    }
    return false;
}
bool rWest(const Arena& a, int r, int c)
{
    if (c == 1)
    {
        return true;
    }
    else
    {
        if (a.numberOfRabbitsAt(r, c -1) != 0)
        {
            return true;
        }
    }
    return false;
}
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    
  

    int rAtOrigin = checkAdjecent(a, r, c);

    int rAtNorth = 10000;
    int rAtEast = 10000;
    int rAtSouth = 10000;
    int rAtWest = 10000;

    int nums[4] = { 0,1,2,3 };
    if (rNorth(a, r, c))
    {
        nums[0] = 9999;
    }
    if (rEast(a, r, c))
    {
        nums[1] = 9999;
    }
    if (rSouth(a, r, c))
    {
        nums[2] = 9999;
    }
    if (rWest(a, r, c))
    {
        nums[3] = 9999;
    }

    if (nums[0] == 0)
    {
        rAtNorth = checkAdjecent(a, r - 1, c);
    }
    if (nums[1] == 1)
    {
        rAtEast = checkAdjecent(a, r, c+1);
    }
    if (nums[2] == 2)
    {
        rAtSouth = checkAdjecent(a, r+1, c);
    }
    if (nums[3] == 3)
    {
        rAtWest = checkAdjecent(a, r, c-1);
    }
    
    int minRab[5] = {rAtNorth, rAtEast, rAtSouth, rAtWest, rAtOrigin};

    int currMin = rAtOrigin;
    int dir = 4;
    for (int i = 0; i < 5; i++)
    {
        if (minRab[i] < currMin)
        {
            dir = i;
            currMin = minRab[i];
        }
    }

    if (dir < 4)
    {
        bestDir = dir;
        return true;
    }
    else 
    {
        return false;
    }
 
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr || strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif