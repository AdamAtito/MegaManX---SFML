#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
using namespace sf;
using namespace std;

// Game States
// Game States
enum GameState {
    MAIN_MENU,
    PLAYING,
    CREATING,
    INSTRUCTIONS,
    PAUSED,
    GAME_OVER,
    EXIT_GAME,
    WIN_STATE,
    OPTIONS
};


Music winMusic;

Text winnerText;

Clock winClock;
float winDuration = 3.0f;

struct Confetti {
    Sprite sprite;
    int frame;
    float timer;
    Vector2f velocity;
    float lifetime;
    bool active;
    Confetti() : frame(0), timer(0), lifetime(2.0f), active(false) {}
};

vector<Confetti> confettiParticles;
Texture confettiTexture;
const int confettiFrameCount = 10;
const float confettiAnimationSpeed = 0.1f;
const int confettiFrameWidth = 32;
const int confettiFrameHeight = 32;
SoundBuffer damageBuffer;
Sound damageSound;
Music stageMusic;

const int BOSS_COUNT = 2;
// Global Sprites
Sprite mapSprite;
Sprite carSprite;
Sprite carSprite2;
Sprite trackSprite;
Sprite backgroundSprite;
Sprite megamansprite;
Sprite readysprite;
Texture attackDeathTex;
Texture dieEffect;
Texture healthBar;
Sprite Health_Bar;
Sprite tall_notbroken;
Texture tall_notbokenTex;
Sprite tall_notbroken2;
Texture tall_notbroken2Tex;
Sprite tall_broken;
Texture tall_brokenTex;
Texture bossDeathTex;
Sprite bossDeath[BOSS_COUNT];

// Menu Sprites
Sprite backg1, backp1, backc1, name1, arrow1, head1, sh1;

// FinalBoss Struct
struct FinalBoss {
    Sprite sprite;
    int frame;
    int direction;
    float timer;
    bool isIdle;
    bool isSliding;
    bool isWalking;
    bool isAttacking;
    float speed;
    int Health;
    int Damage;
    bool isActive = false;
    bool isdead;
    bool isdying;
    int deathFrame;
    float deathTimer;
    const float deathAnimationSpeed = 0.1f;
    RectangleShape EnemyCollider;
    FinalBoss() : frame(0), direction(1), timer(0), isIdle(true), isSliding(false), isWalking(false), isAttacking(false), speed(2.0f), Health(50), Damage(8), isdead(false), isdying(false), deathFrame(0), deathTimer(0) {}
};
FinalBoss finalBoss;

Texture healthupTex;
//Health Up Struct
struct healthUp {
    Sprite sprite;
    int health = 2;
    float healthUpAnimationSpeed = 0.15f;
    float healthUpTimer;
    int frame;
    Vector2f Position;
    bool gotHealthUp = false;
};
healthUp healthUps[5];
void Health_Up(Vector2f, float, int);

// Map Collisions
RectangleShape playerCollider(Vector2f(29, 33));
RectangleShape rectangle0(Vector2f(745, 48));
RectangleShape rectangle1(Vector2f(482.48, 45.417));
RectangleShape rectangle2(Vector2f(991, 47));
RectangleShape rectangle3(Vector2f(400, 47));
RectangleShape rectangle_toward3(Vector2f(97, 47));
RectangleShape rectangle_forbroken(Vector2f(199, 15));
RectangleShape rectangle4(Vector2f(477, 47));
RectangleShape rectangle_toward4(Vector2f(288, 47));
RectangleShape rectangle_forbroken4(Vector2f(199, 15));
RectangleShape slantedEdge0(Vector2f(129, 40));
RectangleShape rectangle5(Vector2f(95.5, 47));
RectangleShape rectangle6(Vector2f(195, 47));
RectangleShape rectangle7(Vector2f(66, 47));
RectangleShape rectangle8(Vector2f(66, 47));
RectangleShape rectangle9(Vector2f(228, 47));
RectangleShape rectangle10(Vector2f(64, 47));
RectangleShape slantedEdge1(Vector2f(133.5, 47));
RectangleShape rectangle11(Vector2f(302, 47));
RectangleShape rectangle12(Vector2f(292, 47));
RectangleShape rectangle13(Vector2f(456, 47));
RectangleShape rectangle14(Vector2f(420, 47));

Texture mapTexture;
Texture backgroundTexture;
Sprite map2;
Texture map2texture;
bool isplayer = false;

// Textures
Texture readytexture;
Texture megamanIdle;
Texture megamanRun;
Texture megamanJump;
Texture megamanShoot;
Texture megamanJumpShoot;
Texture megamanShootRun;
Texture megamanFall;
Texture bulletenemyTexture;
Texture megamanDamaged;
Texture BossBulletTexture;
Texture finalBossIdleTex;
Texture finalBossSlideTex;
Texture finalBossWalkTex;
Texture finalBossAttackTex;
Texture bulletTex;
Texture bombTexture;
Texture explosionTexture;
Texture megamanClimb;
Texture strongBulletTex;
Texture chargingTex;
Sprite chargingSprite;


bool isTallNotBrokenVisible = true;
bool isTall4visible = true;

RectangleShape climbing_area;
bool isClimbing = false;
float climbSpeed = 100.0f;
RectangleShape climbing2_area;
bool isClimbing2 = false;


// Animation Variables
int jumpanimationtimer = 0;
float shootrunanimationtimer = 0;
int shootanimationtimer = 0;
int runanimationtimer = 0;
int jumpshootanimationtimer = 0;
int readyanimationtimer = 0;
const float nearGroundThreshold = 50.0f;
const float jumpanimationspeed = 2.5;
const int runanimationspeed = 2;
const int jumpshootspeed = 3;
const float readyanimationspeed = 0.04f;
const int shootanimationspeed = 5;
const float shootrunanimationspeed = 2;
float falltimer = 0;
const int fallspeed = 4;
int readyindx = 0;
int Idleindx = 0;
int Fallindx = 0;
int Runindx = 0;
int Jumpindx = 0;
int Shootindx = 0;
int ShootRunindx = 0;
int JumpShootindx = 0;
bool showready = true;
Clock readyclock;
float readyduration = 2.0f;
int Health = 18;
int damageFrame = 0;
float damageTimer = 0.0f;
float DamageAnimationSpeed = 0.15f;
float RestTimer = 0.0f;
float RestDuration = 1.0f;
const float getStepBack = 10.0f;
bool megamandamaged = false;
bool megaManDead = false;


int facingDirection = 1;
bool ismoving = false;
bool isJumping = false;

// Bullet Struct
struct Bullet {
    Sprite sprite;
    Vector2f velocity;
    int damage = 2;
    bool isStrong = false;
    bool isForming = false;
    float animationTimer = 0.0f;
    int frame = 0;
    float formingDuration = 0.5f;
    int chargingFrame = 0;
    RectangleShape bulletCollider;
    void upDate(float deltaTime) {
        bulletCollider.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        bulletCollider.setFillColor(Color::Black);
        if (isStrong && isForming == 0) {
            if (facingDirection == 1) {
                bulletCollider.setPosition(sprite.getPosition().x + 72, sprite.getPosition().y + 55);
            }
            else {
                bulletCollider.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y + 55);
            }
        }
        else {
            if (facingDirection == 1) {
                bulletCollider.setPosition(sprite.getPosition().x + 13, sprite.getPosition().y + 10);
            }
            else {
                bulletCollider.setPosition(sprite.getPosition().x - 4, sprite.getPosition().y + 10);
            }
        }

        if (isForming) {
            if (facingDirection == 1) {
                bulletCollider.setPosition(sprite.getPosition().x + 55, sprite.getPosition().y + 55);
            }
            else {
                bulletCollider.setPosition(sprite.getPosition().x, sprite.getPosition().y + 55);
            }            animationTimer += deltaTime * 1.5;
            if (animationTimer >= 0.1f) {
                frame++;
                chargingFrame++;
                if (frame >= 5) {
                    frame = 5;
                    isForming = false;
                    velocity = Vector2f(250 * (sprite.getScale().x > 0 ? 1 : -1), 0);
                }
                sprite.setTextureRect(IntRect(frame * 72, 0, 72, 66));
                chargingSprite.setTextureRect(IntRect(chargingFrame * 40, 0, 40, 40));
                if (isJumping) {
                    if (facingDirection == 1) {
                        chargingSprite.setPosition(megamansprite.getPosition().x - 29, megamansprite.getPosition().y - 20);
                        sprite.setPosition(megamansprite.getPosition().x - 10, megamansprite.getPosition().y - 25);
                    }
                    else {
                        chargingSprite.setPosition(megamansprite.getPosition().x - 18, megamansprite.getPosition().y - 20);
                        sprite.setPosition(megamansprite.getPosition().x + 8, megamansprite.getPosition().y - 25);
                    }
                }
                else {
                    if (facingDirection == 1) {
                        chargingSprite.setPosition(megamansprite.getPosition().x - 20, megamansprite.getPosition().y - 20);
                    }
                    else {
                        chargingSprite.setPosition(megamansprite.getPosition().x - 30, megamansprite.getPosition().y - 20);
                    }
                }
                animationTimer = 0.0f;
            }
            if (ismoving) {
                if (facingDirection == 1) {
                    velocity = Vector2f(250, 0);
                    sprite.move(velocity * deltaTime);
                    bulletCollider.move(velocity * deltaTime);
                    sprite.setPosition(megamansprite.getPosition().x + 8, megamansprite.getPosition().y - 25);
                }
                else {
                    velocity = Vector2f(-250, 0);
                    sprite.move(velocity * deltaTime);
                    bulletCollider.move(velocity * deltaTime);
                    sprite.setPosition(megamansprite.getPosition().x, megamansprite.getPosition().y - 25);
                }

            }
        }
        else {
            sprite.move(velocity * deltaTime);
            bulletCollider.move(velocity * deltaTime);

        }
    }
};
vector<Bullet> bullets;

bool CWasPressed = false;
bool XWasPressed = false;
const float StartFormingStrongBullet = 0.05f;
float shootCooldown = 0.0f;
const float shootCooldownTime = 0.2f;

SoundBuffer shootBuffer;
Sound shootSound; vector<Sound> shootSounds;
const int maxShootSounds = 100;

SoundBuffer chargeShootBuffer;
Sound chargeShootSound; vector<Sound> chargeShootSounds;
const int maxChargeShootSounds = 100;

SoundBuffer fadeinBuffer;
Sound fadeinSound;

// Game State Variables
bool isfalling = true;
bool isFallingFast = false;
float fastFallVelocity = 0.0f;
const float fastFallGravity = 6.5f;
float velocityY = 0;
bool shooting = false;
bool shootfinished = false;
bool falldone = false;
const float gravity = 0.3f;
const float jumpStrength = -7.5;
float groundlevel = 290.0;
const float gravityfall = 1.5f;
float deltaTime;
int jumpstate[] = { 0, 1, 2, 3, 4, 5, 6 };
const int jumpShootFramesCount = 5;
float angle = 0.f;
bool isFired = false;

// Window and View
RenderWindow window(VideoMode(1280, 720), "Mega Man X");
View view(FloatRect(0, 0, 800, 600));

// Enemy Bullet Struct
struct BulletEnemy {
    Sprite sprite;
    float velocityX;
    bool active;
    int damage = 1;
};
vector<BulletEnemy> bulletsenemy;
const float bulletenemySpeed = -300.0f;
const int bulletenemyFrameWidth = 42;
const int bulletenemyFrameHeight = 38;
const int bulletenemyFrameCount = 1;

// Boss Bullet Struct
struct bossBullet {
    Sprite bossSprite;
    float boosVelocityX = 10.f * cos(angle * 3.14159f / 180.f);
    float bossVelocityY = -10.f * sin(angle * 3.14159f / 180.f);
    bool bossActive;
    int damage = 1;
    RectangleShape hitbox;
    int bossIndex;
};
vector<bossBullet> bossBullets;
const float bossBulletSpeed = -600.0f;
const int bossBulletFrameWidth = 64;
const int bossBulletFrameHeight = 63;
const int bossBulletFrameCount = 1;

// Bomb Struct
struct Bomb {
    Sprite sprite;
    float velocityY;
    bool active;
    RectangleShape hitbox;
};

vector<Bomb> bombs;
const float bombSpeed = 200.0f;
const int bombFrameWidth = 55;
const int bombFrameHeight = 56;
const float proximityDistance = 40.0f;

Vector2f playerPos = megamansprite.getPosition();
float speedf = 7;
Vector2f Normalize(Vector2f vectorr) {
    float mag = sqrt(pow(vectorr.x, 2) + pow(vectorr.y, 2));
    Vector2f res = Vector2f(vectorr.x / mag, vectorr.y / mag);
    return res;
}

// Explosion Struct
struct Explosion {
    Sprite sprite;
    int frame;
    int damage = 1;
    float timer;
    bool active;
    float animationSpeed = 0.1f;
    int frameCount = 7;
    int frameWidth = 74;
    int frameHeight = 72;
    float lifetime = 2.0f;
    RectangleShape hitbox; // Add hitbox for collision detection
    float velocityY; // Add velocity for potential movement
    Explosion() : frame(0), timer(0), active(false) {}
};
vector<Explosion> explosions;

SoundBuffer jumpBuffer;
Sound jumpSound;

// Enemy Struct
struct Enemy {
    Sprite sprite;
    int frame;
    int direction = 1;
    int Health;
    int Damage;
    bool isdead = false;
    bool isdying = false;
    int deathFrame = 0;
    float deathTimer = 0;
    const float deathAnimationSpeed = 0.1f;
    RectangleShape EnemyCollider;
    Vector2f velocity;
};

const int ENEMY_COUNT = 5;
const int MONSTER_COUNT = 3;
const int ATTACK_COUNT = 4;
const int fly_count = 5;
const int Flying_count = 5;

Enemy enemies[ENEMY_COUNT];
Enemy monsters[MONSTER_COUNT];
Enemy bosses[BOSS_COUNT];;
Enemy attack[ATTACK_COUNT];
Enemy Fly[fly_count];
Enemy flyingBot[Flying_count];

Texture enemiesTex;
Texture Monster1;
Texture big_boss;
Texture attacks;
Texture FLY;
Texture FLYING_BOT;

// Menu Variables
Font font;
SoundBuffer menubuffer, keybuffer, losebuffer;
Sound menusound, keysound, losesound;
vector<string> playerNames = { "Mahera Modather", "Adam Atito", "Mariam Maher", "Tarek Mohamed", "Dana Mohamed", "Mohamed Maher", "Roaa Mohamed" };
GameState gameState = MAIN_MENU;
int menuSelection = 0;
bool isAnimating = false;

void Start();
void Start_Enemies();
void Update();
void Update_Enemies();
void PlayerMovement();
void Draw();
void UpdateBulletsenemy();
void ShootBulletenemy(Vector2f position, int enemyIndex);
void BossUpdateBullets();
void bossShootBullet(Vector2f);
void Shooting();
void HandelingBullets();
void DamageMegaMan(int, Vector2f);
void MegaManHealth();
void UpdateBombs();
void ShootBomb(Vector2f position);
void SpawnExplosion(Vector2f position);
void UpdateExplosions();
void drawMainMenu(RenderWindow& window, Font& font, int selectedItem);
void drawPauseMenu(RenderWindow& window, Font& font, int selectedItem);
void drawCreatingScreen(RenderWindow& window, Font& font, const vector<string>& names);
void drawInstructions(RenderWindow& window, Font& font);
void drawGameOverMenu(RenderWindow& window, Font& font, int selectedItem);
float globalVolume = 100.0f;
bool isMuted = false;
RectangleShape volumeSliderBar;
RectangleShape volumeSliderHandle;
Text volumeText;
Text muteText;
RectangleShape muteCheckbox;
bool isDraggingSlider = false;
int optionsSelection = 0;
void drawOptionsMenu(RenderWindow& window, Font& font, int selectedItem);
void updateVolume();
void initializeConfetti();
void updateConfetti(float deltaTime);
void reset();

int main()
{
    window.setFramerateLimit(30);
    view.zoom(0.37f);

    // Load Game Resources (unchanged)
    Texture mapTexture;
    if (!mapTexture.loadFromFile("C:/SFML Template/Mega Man X material/SNES_-_Mega_Man_X_-_Intro_Stageee.png")) {
        cout << "failed to load map" << endl;
        return -1;
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setPosition(-10.0f, 184.0f);

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/SFML Template/Mega Man X material/IMG_20250426_175037_2.png")) {
        cout << "failed to load background!" << endl;
        return -1;
    }
    backgroundSprite.setTexture(backgroundTexture);
    Vector2u mapSize = mapTexture.getSize();
    Vector2u bgSize = backgroundTexture.getSize();
    float scaleFactor = 1.185f;
    backgroundSprite.setScale(
        static_cast<float>(mapSize.x) / (bgSize.x + 1100) * scaleFactor,
        static_cast<float>(mapSize.y) / (bgSize.y - 60) * scaleFactor
    );
    backgroundSprite.move(0.0f, -40.0f);

    Texture carTexture;
    if (!carTexture.loadFromFile("C:/SFML Template/Mega Man X material/car.png")) {
        cout << "failed to load car image" << endl;
        return -1;
    }
    carSprite.setTexture(carTexture);

    Texture carTexture2;
    if (!carTexture2.loadFromFile("C:/SFML Template/Mega Man X material/car2.png")) {
        cout << "failed to load second car image" << endl;
        return -1;
    }
    carSprite2.setTexture(carTexture2);

    Texture trackTexture;
    if (!trackTexture.loadFromFile("C:/SFML Template/Mega Man X material/track.png")) {
        cout << "failed to load track image" << endl;
        return -1;
    }
    trackSprite.setTexture(trackTexture);

    float carSpeed = 100.0f;
    float trackSpeed = 120.0f;
    float carStartX = 600.0f;
    float carEndX = -100.0f;
    float trackStartX = 700.0f;
    float trackEndX = -100.0f;
    carSprite.setPosition(carStartX, 278.0f);
    carSprite2.setPosition(carStartX + 200.0f, 280.0f);
    trackSprite.setPosition(trackStartX + 250.0f, 280.0f);

    // Load Menu Resources (unchanged)
    Texture backg, backp, backc, name, head, arrow, sh;
    if (!backg.loadFromFile("C:/SFML Template/Mega Man X material/X3.png") ||
        !backp.loadFromFile("C:/SFML Template/Mega Man X material/bg4.png") ||
        !backc.loadFromFile("C:/SFML Template/Mega Man X material/bg5.png") ||
        !name.loadFromFile("C:/SFML Template/Mega Man X material/logo_orig.png") ||
        !head.loadFromFile("C:/SFML Template/Mega Man X material/favicon.png") ||
        !arrow.loadFromFile("C:/SFML Template/Mega Man X material/cursor.png") ||
        !sh.loadFromFile("C:/SFML Template/Mega Man X material/enemy-red-shoot.png") ||
        !font.loadFromFile("C:/SFML Template/Mega Man X material/BigSpace-rPKx.ttf")) {
        cerr << "Failed to load one or more menu resources.\n";
        return -1;
    }

    backg1.setTexture(backg);
    backg1.setScale(static_cast<float>(window.getSize().x) / backg.getSize().x, static_cast<float>(window.getSize().y) / backg.getSize().y);
    backp1.setTexture(backp);
    backp1.setScale(static_cast<float>(window.getSize().x) / backp.getSize().x, static_cast<float>(window.getSize().y) / backp.getSize().y);
    backc1.setTexture(backc);
    backc1.setScale(static_cast<float>(window.getSize().x) / backc.getSize().x, static_cast<float>(window.getSize().y) / backc.getSize().y);
    name1.setTexture(name);
    name1.setPosition(5.0f, 20.0f);
    name1.setScale(0.45f, 0.5f);
    arrow1.setTexture(arrow);
    arrow1.setScale(2.5f, 2.0f);
    head1.setTexture(head);
    head1.setScale(2.5f, 2.0f);
    sh1.setTexture(sh);
    sh1.setScale(2.5f, 2.0f);
    if (!confettiTexture.loadFromFile("C:/SFML Template/Mega Man X material/sprite10_strip10.png")) {
        cout << "Failed to load confetti sprite sheet!" << endl;
    }
    if (!menubuffer.loadFromFile("C:/SFML Template/Mega Man X material/menu.oga") ||
        !keybuffer.loadFromFile("C:/SFML Template/Mega Man X material/key.wav") ||
        !losebuffer.loadFromFile("C:/SFML Template/Mega Man X material/lose.oga")) {
        cerr << "Failed to load one or more sound files.\n";
        return -1;
    }
    menusound.setBuffer(menubuffer);
    keysound.setBuffer(keybuffer);
    losesound.setBuffer(losebuffer);
    if (!winMusic.openFromFile("C:/SFML Template/Mega Man X material/success-fanfare-trumpets-6185.wav")) {
        cout << "Failed to load win music!" << endl;
    }
    winMusic.setLoop(false);

    // Initialize winner text
    winnerText.setFont(font);
    winnerText.setString("WINNER");
    winnerText.setCharacterSize(150);
    winnerText.setFillColor(Color::Yellow);

    // Initialize Options Menu Elements
    volumeSliderBar.setSize(Vector2f(200.0f, 20.0f));
    volumeSliderBar.setFillColor(Color(100, 100, 100));
    volumeSliderBar.setPosition(600.0f, 300.0f);
    volumeSliderHandle.setSize(Vector2f(20.0f, 40.0f));
    volumeSliderHandle.setFillColor(Color::Red);
    volumeSliderHandle.setPosition(600.0f + (globalVolume / 100.0f) * 200.0f - 10.0f, 290.0f);
    volumeText.setFont(font);
    volumeText.setCharacterSize(40);
    volumeText.setFillColor(Color::White);
    volumeText.setPosition(350.0f, 290.0f);
    muteText.setFont(font);
    muteText.setString("Mute");
    muteText.setCharacterSize(40);
    muteText.setFillColor(Color::White);
    muteText.setPosition(350.0f, 390.0f);
    muteCheckbox.setSize(Vector2f(30.0f, 30.0f));
    muteCheckbox.setFillColor(isMuted ? Color::Green : Color::White);
    muteCheckbox.setOutlineColor(Color::Black);
    muteCheckbox.setOutlineThickness(2.0f);
    muteCheckbox.setPosition(700.0f, 390.0f);

    // Initialize Game
    Start();
    Start_Enemies();
    Clock clock;

    // Declare variables outside switch to avoid C2360/C2361
    Vector2f playerCenter;
    Vector2f camSize;
    Vector2f newViewCenter;
    float halfCamW;
    float halfCamH;
    float maxCamX;
    float minCamX;
    float maxCamY;
    float minCamY;
    float mapWidth;
    float bgWidth;
    float bgMoveFactor;
    float bgX;
    Vector2f carPos;
    Vector2f carPos2;
    Vector2f trackPos;

    while (window.isOpen()) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i pixelPos = Mouse::getPosition(window);
            Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
            cout << "Map Coordinates: " << worldPos.x << " " << worldPos.y << endl;
        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && !isAnimating) {
                if (gameState == MAIN_MENU) {
                    if (event.key.code == Keyboard::Up) {
                        keysound.play();
                        menuSelection = (menuSelection + 4) % 5;
                    }
                    else if (event.key.code == Keyboard::Down) {
                        keysound.play();
                        menuSelection = (menuSelection + 1) % 5;
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        keysound.play();
                        isAnimating = true;
                        sh1.setPosition(70.0f, 320.0f + menuSelection * 60.0f);
                    }
                }
                else if (gameState == PAUSED) {
                    if (event.key.code == Keyboard::Up) {
                        keysound.play();
                        menuSelection = (menuSelection + 2) % 3;
                    }
                    else if (event.key.code == Keyboard::Down) {
                        keysound.play();
                        menuSelection = (menuSelection + 1) % 3;
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        isAnimating = true;
                        sh1.setPosition(340.0f, 330.0f + menuSelection * 80.0f);
                    }
                }
                else if (gameState == GAME_OVER) {
                    if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Down) {
                        keysound.play();
                        menuSelection = (menuSelection + 1) % 2;
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        isAnimating = true;
                        sh1.setPosition(340.0f, 330.0f + menuSelection * 80.0f);
                    }
                }
                else if (gameState == OPTIONS) {
                    if (event.key.code == Keyboard::Up) {
                        keysound.play();
                        optionsSelection = (optionsSelection + 2) % 3;
                    }
                    else if (event.key.code == Keyboard::Down) {
                        keysound.play();
                        optionsSelection = (optionsSelection + 1) % 3;
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        shootSound.play();
                        if (optionsSelection == 1) {
                            isMuted = !isMuted;
                            muteCheckbox.setFillColor(isMuted ? Color::Green : Color::White);
                            updateVolume();
                        }
                        else if (optionsSelection == 2) {
                            gameState = MAIN_MENU;
                            menuSelection = 0;
                        }
                    }
                    else if (optionsSelection == 0 && event.key.code == Keyboard::Left) {
                        globalVolume = max(0.0f, globalVolume - 5.0f);
                        volumeSliderHandle.setPosition(600.0f + (globalVolume / 100.0f) * 200.0f - 10.0f, 290.0f); // Updated x-position
                        updateVolume();
                    }
                    else if (optionsSelection == 0 && event.key.code == Keyboard::Right) {
                        globalVolume = min(100.0f, globalVolume + 5.0f);
                        volumeSliderHandle.setPosition(600.0f + (globalVolume / 100.0f) * 200.0f - 10.0f, 290.0f); // Updated x-position
                        updateVolume();
                    }
                }
                else if ((gameState == CREATING || gameState == INSTRUCTIONS) && event.key.code == Keyboard::Enter) {
                    gameState = MAIN_MENU;
                    menuSelection = 0;
                }
            }
            // Handle mouse events for volume slider
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && gameState == OPTIONS) {
                Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (volumeSliderHandle.getGlobalBounds().contains(mousePos)) {
                    isDraggingSlider = true;
                }
                else if (muteCheckbox.getGlobalBounds().contains(mousePos) && optionsSelection == 1) {
                    isMuted = !isMuted;
                    muteCheckbox.setFillColor(isMuted ? Color::Green : Color::White);
                    updateVolume();
                    shootSound.play();
                }
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                isDraggingSlider = false;
            }
            else if (event.type == Event::MouseMoved && isDraggingSlider && gameState == OPTIONS) {
                Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y));
                float newX = min(max(mousePos.x, 600.0f), 800.0f); // Updated bounds: 600.0f to 800.0f
                volumeSliderHandle.setPosition(newX - 10.0f, 290.0f);
                globalVolume = ((newX - 600.0f) / 200.0f) * 100.0f; // Updated base position
                updateVolume();
            }
        }
        deltaTime = clock.restart().asSeconds();
        
        // Music handling logic
        if (gameState == PLAYING) {
            if (stageMusic.getStatus() != Music::Playing) {
                stageMusic.play();
            }
        }

        if (gameState == PLAYING && stageMusic.getStatus() == Music::Stopped) {
            stageMusic.play();
        }
        if (gameState == MAIN_MENU || gameState == CREATING || gameState == INSTRUCTIONS || gameState == PAUSED || gameState == OPTIONS) {
            if (menusound.getStatus() == Sound::Stopped) {
                menusound.play();
            }
        }
        else {
            if (menusound.getStatus() == Sound::Playing) {
                menusound.stop();
            }
        }
        if (gameState == GAME_OVER) {
            if (losesound.getStatus() == Sound::Stopped) {
                losesound.play();
            }
        }
        else {
            if (losesound.getStatus() == Sound::Playing) {
                losesound.stop();
            }
        }

        window.clear();

        switch (gameState) {
        case MAIN_MENU:
            stageMusic.stop();
            window.setView(window.getDefaultView());
            drawMainMenu(window, font, menuSelection);
            if (isAnimating) {
                sh1.setPosition(sh1.getPosition().x, 320.0f + menuSelection * 60.0f);
                window.draw(sh1);
                if (sh1.getPosition().x < 400.0f)
                    sh1.move(10.0f, 0.0f);
                else {
                    isAnimating = false;
                    switch (menuSelection) {
                    case 0:
                        reset();
                        gameState = PLAYING;
                        Health = 18;
                        megaManDead = false;
                        megamansprite.setPosition(400.0f, 0.0f);
                        showready = true;
                        readyclock.restart();
                        break;
                    case 1: gameState = CREATING; break;
                    case 2: gameState = INSTRUCTIONS; break;
                    case 3: gameState = OPTIONS; optionsSelection = 0; break;
                    case 4: window.close(); break;
                    }
                }
            }
            break;

        case PLAYING:
            if (Keyboard::isKeyPressed(Keyboard::P)) {
                gameState = PAUSED;
                menuSelection = 0;
                if (stageMusic.getStatus() == Music::Playing) {
                    stageMusic.pause();
                }
            }

            // Update Camera
            playerCenter = megamansprite.getPosition();
            camSize = view.getSize();
            newViewCenter = view.getCenter();
            halfCamW = camSize.x / 2.0f;
            halfCamH = camSize.y / 2.0f;
            maxCamX = static_cast<float>(mapTexture.getSize().x) - halfCamW; // Cast to float
            minCamX = halfCamW;
            maxCamY = static_cast<float>(mapTexture.getSize().y) - halfCamH; // Cast to float
            minCamY = halfCamH;

            if (playerCenter.y >= 360.0f && playerCenter.x >= 2379 && playerCenter.x <= 2795) {
                newViewCenter.x = view.getCenter().x;
                newViewCenter.y = playerCenter.y;
            }
            else if (playerCenter.y >= 360.0f && playerCenter.x >= 3205 && playerCenter.x <= 3418) {
                newViewCenter.x = view.getCenter().x;
                newViewCenter.y = playerCenter.y;
            }
            else {
                newViewCenter.x = playerCenter.x; // Follow player horizontally
                newViewCenter.y = 300.0f; // Default Y center
            }


            // Clamp camera to map boundaries
            newViewCenter.x = std::max(minCamX, std::min(newViewCenter.x, maxCamX));
            newViewCenter.y = std::max(minCamY, std::min(newViewCenter.y, maxCamY));
            view.setCenter(newViewCenter);

            // Background Parallax
            mapWidth = static_cast<float>(mapTexture.getSize().x);
            bgWidth = static_cast<float>(backgroundTexture.getSize().x) * backgroundSprite.getScale().x;
            bgMoveFactor = (bgWidth - static_cast<float>(window.getSize().x)) / (mapWidth - static_cast<float>(window.getSize().x));
            bgX = (view.getCenter().x - static_cast<float>(window.getSize().x) / 12.0f) * bgMoveFactor;
            backgroundSprite.setPosition(-bgX, backgroundSprite.getPosition().y);

            // Car Movement
            carPos = carSprite.getPosition();
            if (carPos.x > carEndX) {
                carPos.x -= carSpeed * deltaTime;
                if (carPos.x < carEndX)
                    carPos.x = carEndX;
                carSprite.setPosition(carPos);
            }

            carPos2 = carSprite2.getPosition();
            if (carPos2.x > carEndX) {
                carPos2.x -= carSpeed * deltaTime;
                if (carPos2.x < carEndX)
                    carPos2.x = carEndX;
                carSprite2.setPosition(carPos2);
            }

            trackPos = trackSprite.getPosition();
            if (trackPos.x > trackEndX) {
                trackPos.x -= trackSpeed * deltaTime;
                if (trackPos.x < trackEndX)
                    trackPos.x = trackEndX;
                trackSprite.setPosition(trackPos);
            }

            // Game Logic
            Update_Enemies();
            Update();
            UpdateBulletsenemy();
            UpdateBombs();
            UpdateExplosions();
            BossUpdateBullets();
            Draw();
            break;

        case CREATING:
            window.setView(window.getDefaultView());
            drawCreatingScreen(window, font, playerNames);
            break;

        case INSTRUCTIONS:
            window.setView(window.getDefaultView());
            drawInstructions(window, font);
            break;

        case PAUSED:
            window.setView(window.getDefaultView());
            drawPauseMenu(window, font, menuSelection);
            if (isAnimating) {
                sh1.setPosition(sh1.getPosition().x, 330.0f + menuSelection * 80.0f);
                window.draw(sh1);
                if (sh1.getPosition().x < 660.0f)
                    sh1.move(10.0f, 0.0f);
                else {
                    isAnimating = false;
                    switch (menuSelection) {
                    case 0: gameState = PLAYING; break;
                    case 1: gameState = MAIN_MENU; menuSelection = 0; break;
                    case 2: window.close(); break;
                    }
                }
            }
            break;

        case GAME_OVER:
            stageMusic.stop();
            window.setView(window.getDefaultView());
            drawGameOverMenu(window, font, menuSelection);
            if (isAnimating) {
                sh1.setPosition(sh1.getPosition().x, 330.0f + menuSelection * 120.0f);
                window.draw(sh1);
                if (sh1.getPosition().x < 660.0f)
                    sh1.move(10.0f, 0.0f);
                else {
                    isAnimating = false;
                    switch (menuSelection) {
                    case 0:
                        reset();
                        gameState = PLAYING;
                        Health = 18;
                        megaManDead = false;
                        megamansprite.setPosition(400.0f, 0.0f);
                        showready = true;
                        readyclock.restart();
                        Start_Enemies();
                        break;
                    case 1: window.close(); break;
                    }
                }
            }
            break;

        case WIN_STATE:
            stageMusic.stop();
            window.setView(view);
            Draw();
            winnerText.setPosition(window.getSize().x - 900, (window.getSize().y - 700));
            window.draw(winnerText);
            if (winClock.getElapsedTime().asSeconds() >= winDuration) {
                gameState = MAIN_MENU;
                menuSelection = 0;
                winMusic.stop();
                confettiParticles.clear();
            }
            updateConfetti(deltaTime);
            break;

        case OPTIONS:
            window.setView(window.getDefaultView());
            drawOptionsMenu(window, font, optionsSelection);
            break;

        default:
            break;
        }

        window.display();
    }

    return 0;
}

// Menu Drawing Functions
void drawMainMenu(RenderWindow& window, Font& font, int selectedItem) {
    string options[] = { "Play", "Credit", "Instructions", "Options", "Quit" };
    window.draw(backg1);
    window.draw(name1);
    head1.setPosition(50, 310 + selectedItem * 60);
    window.draw(head1);
    for (int i = 0; i < 5; ++i) {
        int fontSize = (i == selectedItem) ? 50 : 40;
        Text text(options[i], font, fontSize);
        text.setPosition(100, 300 + i * 60);
        text.setFillColor(i == selectedItem ? Color::Red : Color::White);
        window.draw(text);
    }
}

void drawPauseMenu(RenderWindow& window, Font& font, int selectedItem) {
    string options[] = { "Continue", "Main Menu", "Quit" };
    window.draw(backp1);
    Text pause("Pause Menu", font, 100);
    pause.setPosition(300, 50);
    pause.setFillColor(Color::Yellow);
    window.draw(pause);
    head1.setPosition(300, 310 + selectedItem * 80);
    window.draw(head1);
    for (int i = 0; i < 3; ++i) {
        int fontSize = (i == selectedItem) ? 50 : 40;
        Text text(options[i], font, fontSize);
        text.setPosition(400, 300 + i * 80);
        text.setFillColor(i == selectedItem ? Color::Red : Color::White);
        window.draw(text);
    }
}

void drawCreatingScreen(RenderWindow& window, Font& font, const vector<string>& names) {
    window.draw(backc1);
    Text credit("Credit", font, 140);
    credit.setPosition(340, 2);
    credit.setFillColor(Color::Yellow);
    window.draw(credit);
    Text back("Back", font, 80);
    back.setPosition(370, 550);
    back.setFillColor(Color::Red);
    window.draw(back);
    for (size_t i = 0; i < names.size(); ++i) {
        Text nameText(names[i], font, 50);
        nameText.setPosition(150, 170 + i * 50);
        nameText.setFillColor(Color::White);
        window.draw(nameText);
        arrow1.setPosition(90, 190 + i * 50);
        window.draw(arrow1);
    }
}

void drawInstructions(RenderWindow& window, Font& font) {
    window.draw(backc1);
    Text instructions("Instructions", font, 100);
    instructions.setPosition(200, 2);
    instructions.setFillColor(Color::Yellow);
    window.draw(instructions);
    Text back("Back", font, 80);
    back.setPosition(350, 550);
    back.setFillColor(Color::Red);
    window.draw(back);
    Text instructions2("In Mega Man X your goal is to defeat enemies\nto keep alive.\n"
        "You move using A & D buttons,\njump with Space,\n"
        "and shoot with C key.\nTo pause the game, press P.\n"
        "If you run out of health, it is Game Over.", font, 50);
    instructions2.setPosition(50, 100);
    instructions2.setFillColor(Color::White);
    window.draw(instructions2);
    for (int i = 0; i < 7; i++) {
        if (i == 1 || i == 3 || i == 4) continue;
        arrow1.setPosition(3, 120 + i * 60);
        window.draw(arrow1);
    }
}

void drawGameOverMenu(RenderWindow& window, Font& font, int selectedItem) {
    string options[] = { "Play Again", "Quit" };
    window.draw(backp1);
    Text gameOver("GAME OVER", font, 100);
    gameOver.setPosition(330, 50);
    gameOver.setFillColor(Color::Red);
    window.draw(gameOver);
    head1.setPosition(300, 310 + selectedItem * 120);
    window.draw(head1);
    for (int i = 0; i < 2; ++i) {
        int fontSize = (i == selectedItem) ? 50 : 40;
        Text text(options[i], font, fontSize);
        text.setPosition(400, 300 + i * 120);
        text.setFillColor(i == selectedItem ? Color::Red : Color::White);
        window.draw(text);
    }
}

void drawOptionsMenu(RenderWindow& window, Font& font, int selectedItem) {
    window.draw(backc1);
    Text optionsTitle("Options", font, 130);
    optionsTitle.setPosition(330, 20);
    optionsTitle.setFillColor(Color::Yellow);
    window.draw(optionsTitle);

    volumeText.setString("Volume: " + to_string(static_cast<int>(globalVolume)) + "%");
    window.draw(volumeText);
    window.draw(volumeSliderBar);
    window.draw(volumeSliderHandle);

    window.draw(muteText);
    window.draw(muteCheckbox);

    Text back("Back", font, selectedItem == 2 ? 50 : 40);
    back.setPosition(350, 550);
    back.setFillColor(selectedItem == 2 ? Color::Red : Color::White);
    window.draw(back);

    if (selectedItem == 0) {
        head1.setPosition(300, 290);
    }
    else if (selectedItem == 1) {
        head1.setPosition(300, 390);
    }
    else {
        head1.setPosition(300, 550);
    }
    window.draw(head1);
}

void updateVolume() {
    float volume = isMuted ? 0.0f : globalVolume;
    stageMusic.setVolume(volume);
    winMusic.setVolume(volume);
    menusound.setVolume(volume);
    keysound.setVolume(volume);
    losesound.setVolume(volume);
    shootSound.setVolume(volume);
    fadeinSound.setVolume(volume);
    damageSound.setVolume(volume);
    jumpSound.setVolume(volume);
}

// Game Functions
void Start()
{
    groundlevel = 290.0;
    megamanFall.loadFromFile("C:/SFML Template/Mega Man X material/Fall.png");
    megamanIdle.loadFromFile("C:/SFML Template/Mega Man X material/Idle.png");
    megamanRun.loadFromFile("C:/SFML Template/Mega Man X material/Run.png");
    megamanJump.loadFromFile("C:/SFML Template/Mega Man X material/Jump.png");
    megamanShoot.loadFromFile("C:/SFML Template/Mega Man X material/Shoot.png");
    megamanShootRun.loadFromFile("C:/SFML Template/Mega Man X material/ShootRun.png");
    megamanJumpShoot.loadFromFile("C:/SFML Template/Mega Man X material/JumpShoot.png");
    megamanClimb.loadFromFile("C:/SFML Template/Mega Man X material/climb.png");
    readytexture.loadFromFile("C:/SFML Template/Mega Man X material/ready.png");
    bulletenemyTexture.loadFromFile("C:/SFML Template/Mega Man X material/enemy bullet.png");
    BossBulletTexture.loadFromFile("C:/SFML Template/Mega Man X material/bossBullet.png");
    bombTexture.loadFromFile("C:/SFML Template/Mega Man X material/grenade.png");
    explosionTexture.loadFromFile("C:/SFML Template/Mega Man X material/explosion.png");
    attackDeathTex.loadFromFile("C:/SFML Template/Mega Man X material/attack die.png");
    dieEffect.loadFromFile("C:/SFML Template/Mega Man X material/die effect.png");
    shootBuffer.loadFromFile("C:/SFML Template/Mega Man X material/01 - MMX - X Regular Shot.wav");
    chargeShootBuffer.loadFromFile("C:/SFML Template/Mega Man X material/02 - MMX - X Charge Shot.wav");
    fadeinBuffer.loadFromFile("C:/SFML Template/Mega Man X material/17 - MMX - X Fade In.wav");
    bulletTex.loadFromFile("C:/SFML Template/Mega Man X material/Bullet.png");
    strongBulletTex.loadFromFile("C:/SFML Template/Mega Man X material/strong bullet.png");
    chargingTex.loadFromFile("C:/SFML Template/Mega Man X material/charging.png");
    megamanDamaged.loadFromFile("C:/SFML Template/Mega Man X material/Mega_Man_Damaged.png");
    bossDeathTex.loadFromFile("C:/SFML Template/Mega Man X material/boss die.png");
    healthBar.loadFromFile("C:/SFML Template/Mega Man X material/health bar.png");
    tall_notbokenTex.loadFromFile("C:/SFML Template/Mega Man X material/tall_notbroken.png");
    tall_notbroken2Tex.loadFromFile("C:/SFML Template/Mega Man X material/tall_notbroken - Copy.png");
    tall_brokenTex.loadFromFile("C:/SFML Template/Mega Man X material/tall_broken.png");
    map2texture.loadFromFile("C:/SFML Template/Mega Man X material/map(2).png");
    if (!healthupTex.loadFromFile("C:/SFML Template/Mega Man X material/health up.png")) {
        cout << "Failed to load health up  png\n";
    }
    if (!stageMusic.openFromFile("C:/SFML Template/Mega Man X material/Megaman-X-Intro-Stage-Theme.wav")) {
        cout << "Failed to load stage music!" << endl;
    }
    stageMusic.setLoop(true);

    if (!damageBuffer.loadFromFile("C:/SFML Template/Mega Man X material/10 - MMX - X Hurt.wav")) {
        cout << "Failed to load damage sound!" << endl;
    }

    damageSound.setBuffer(damageBuffer);
    jumpBuffer.loadFromFile("C:/SFML Template/Mega Man X material/08 - MMX - X Jump.wav");
    jumpSound.setBuffer(jumpBuffer);
    chargeShootSound.setBuffer(chargeShootBuffer);

    map2.setTexture(map2texture);
    map2.setPosition(-10, 190);

    readysprite.setTexture(readytexture);
    readysprite.setTextureRect(IntRect(0, 0, 76, 63));
    readysprite.setScale(1.3f, 1.3f);
    readysprite.setOrigin(76 / 2.0f, 63 / 2.0f);
    readysprite.setPosition(view.getCenter().x, view.getCenter().y);

    playerCollider.setOrigin(playerCollider.getGlobalBounds().width / 2, playerCollider.getGlobalBounds().height / 2 - 22.5);
    climbing_area.setPosition(2779, 316);
    climbing_area.setSize(Vector2f(40, 220));
    climbing_area.setFillColor(Color::Transparent);
    climbing2_area.setPosition(3418.26, 316);
    climbing2_area.setSize(Vector2f(40, 120));
    climbing2_area.setFillColor(Color::Transparent);

    rectangle0.setPosition(44.8, 283.5);
    rectangle1.setPosition(830.4, 284.583);
    rectangle2.setPosition(1340.33, 283);
    rectangle3.setPosition(2379, 282);
    rectangle_toward3.setPosition(2795, 282);
    rectangle_forbroken.setPosition(2566, 510);
    rectangle4.setPosition(2941.34, 282);
    rectangle_toward4.setPosition(3418.34, 282);
    rectangle_forbroken4.setPosition(3205.66, 510);
    slantedEdge0.setPosition(3770.2, 311.45);
    slantedEdge0.setRotation(14);
    rectangle5.setPosition(3895.13, 292.292);
    rectangle6.setPosition(4058, 300);
    rectangle7.setPosition(4313.81, 267.317);
    rectangle8.setPosition(4410.24, 267.317);
    rectangle9.setPosition(4505, 267.317);
    rectangle10.setPosition(4794.8, 300);
    slantedEdge1.setPosition(4987.5, 309);
    slantedEdge1.setRotation(165);
    rectangle11.setPosition(4992.23, 324.667);
    rectangle12.setPosition(5339.69, 300);
    rectangle13.setPosition(5708.28, 330);
    rectangle14.setPosition(6235.32, 380);

    megamansprite.setTexture(megamanFall);
    megamansprite.setTextureRect(IntRect(0, 0, 71, 92));
    megamansprite.setScale(1, 1);
    megamansprite.setOrigin(67 / 2, 77 / 2);
    megamansprite.setPosition(400, 0);

    tall_notbroken.setTexture(tall_notbokenTex);
    tall_notbroken2.setTexture(tall_notbroken2Tex);
    Health_Bar.setTexture(healthBar);
    Health_Bar.setTextureRect(IntRect(0, 0, 64, 104));
    Health_Bar.setPosition(Vector2f(-50.0f, 70.0f));
    Health_Bar.setScale(4.0f, 3.0f);
    tall_notbroken.setPosition(2520, 288);
    tall_notbroken.setScale(1.0f, 1.0f);
    tall_notbroken2.setPosition(3160.51, 321.508);
    tall_notbroken2.setScale(1.0f, 1.0f);

    shootSound.setBuffer(shootBuffer);
    fadeinSound.setBuffer(fadeinBuffer);
    shootSounds.resize(maxShootSounds);
    for (auto& sound : shootSounds) {
        sound.setBuffer(shootBuffer);
    }
    // Apply initial volume settings
    updateVolume();
    isfalling = true;
    Fallindx = 0;
    falltimer = 0;
    velocityY = 0;
}

void Update()
{
    if (megamansprite.getPosition().x >= 3668) {
        isplayer = true;
    }
    extern GameState gameState;
    playerCollider.setPosition(megamansprite.getPosition());
    if (bosses[0].isdead || bosses[0].isdying) {
        isTallNotBrokenVisible = false;
    }
    if (bosses[1].isdead || bosses[1].isdying) {
        isTall4visible = false;
    }
    bool isOnPlatform = false;

    if (playerCollider.getGlobalBounds().intersects(climbing_area.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Up)) {
        isClimbing = true;
        isJumping = false;
        isfalling = false;
        isFallingFast = false;
        velocityY = 0.0f;
        fastFallVelocity = 0.0f;
    }
    if (playerCollider.getGlobalBounds().intersects(climbing2_area.getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Up)) {
        isClimbing2 = true;
        isJumping = false;
        isfalling = false;
        isFallingFast = false;
        velocityY = 0.0f;
        fastFallVelocity = 0.0f;
    }

    if (isClimbing) {

        megamansprite.setTexture(megamanClimb);
        megamansprite.setTextureRect(IntRect(1, 0, 51, 67));
        float climbDirection = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            climbDirection = -1.0f;
            megamansprite.setTexture(megamanClimb);
            megamansprite.setTextureRect(IntRect(0, 0, 51, 67));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            climbDirection = 1.0f;
        }

        megamansprite.move(0, climbDirection * climbSpeed * deltaTime);


        if (!playerCollider.getGlobalBounds().intersects(climbing_area.getGlobalBounds())) {
            isClimbing = false;
            isfalling = true;
        }


        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            isClimbing = false;
            isJumping = true;
            velocityY = -7.5;
        }


        if (playerCollider.getGlobalBounds().intersects(rectangle0.getGlobalBounds()) ||
            playerCollider.getGlobalBounds().intersects(rectangle3.getGlobalBounds()) && isTallNotBrokenVisible) {
            isClimbing = false;
            isOnPlatform = true;
        }


        float currentY = megamansprite.getPosition().y;
        if (currentY < 326.0f) {
            megamansprite.setPosition(megamansprite.getPosition().x, 247.0f);
            isClimbing = false;
            isOnPlatform = true;
        }
        else if (currentY > 510.0f) {
            megamansprite.setPosition(megamansprite.getPosition().x, 510.0f);
            isClimbing = false;
            isOnPlatform = true;
        }

        return;
    }
    if (isClimbing2) {

        megamansprite.setTexture(megamanClimb);
        megamansprite.setTextureRect(IntRect(1, 0, 51, 67));
        float climbDirection = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            climbDirection = -1.0f;
            megamansprite.setTexture(megamanClimb);
            megamansprite.setTextureRect(IntRect(0, 0, 51, 67));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            climbDirection = 1.0f;
        }

        megamansprite.move(0, climbDirection * climbSpeed * deltaTime);


        if (!playerCollider.getGlobalBounds().intersects(climbing2_area.getGlobalBounds())) {
            isClimbing2 = false;
            isfalling = true;
        }


        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            isClimbing2 = false;
            isJumping = true;
            velocityY = -7.5;
        }


        float currentY = megamansprite.getPosition().y;
        if (currentY < 326.0f) {
            megamansprite.setPosition(megamansprite.getPosition().x, 247.0f);
            isClimbing2 = false;
            isOnPlatform = true;
        }
        else if (currentY > 510.0f) {
            megamansprite.setPosition(megamansprite.getPosition().x, 510.0f);
            isClimbing2 = false;
            isOnPlatform = true;
        }

        return;
    }
    if (playerCollider.getGlobalBounds().intersects(rectangle0.getGlobalBounds())) {
        groundlevel = 294.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle1.getGlobalBounds())) {
        groundlevel = 262.5f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) {
        groundlevel = 278.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (isTallNotBrokenVisible && playerCollider.getGlobalBounds().intersects(rectangle3.getGlobalBounds())) {
        groundlevel = 282.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle_toward3.getGlobalBounds())) {
        groundlevel = 282.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle_forbroken.getGlobalBounds())) {
        groundlevel = 510.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }

    else if (isTall4visible && playerCollider.getGlobalBounds().intersects(rectangle4.getGlobalBounds())) {
        groundlevel = 315.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle_toward4.getGlobalBounds())) {
        groundlevel = 315.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle_forbroken4.getGlobalBounds())) {
        groundlevel = 510.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(slantedEdge0.getGlobalBounds())) {
        float playerX = playerCollider.getPosition().x;
        float edgeX = slantedEdge0.getPosition().x;
        float relativeX = playerX - edgeX;
        float edgeHeight = slantedEdge0.getPosition().y;
        float slope = tan(14 * 3.1415926535 / 180);
        float newGroundLevel = edgeHeight - (relativeX * slope);
        groundlevel = newGroundLevel;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle5.getGlobalBounds())) {
        groundlevel = 280.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle6.getGlobalBounds())) {
        groundlevel = 280.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle7.getGlobalBounds())) {
        groundlevel = 250.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle8.getGlobalBounds())) {
        groundlevel = 250.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle9.getGlobalBounds())) {
        groundlevel = 250.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle10.getGlobalBounds())) {
        groundlevel = 280.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(slantedEdge1.getGlobalBounds())) {
        float playerX = playerCollider.getPosition().x;
        float edgeX = slantedEdge1.getPosition().x;
        float relativeX = playerX - edgeX;
        float edgeHeight = slantedEdge1.getPosition().y;
        float slope = tan(165 * 3.1415926535 / 180);
        float newGroundLevel = edgeHeight - (relativeX * slope);
        groundlevel = newGroundLevel;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle11.getGlobalBounds())) {
        groundlevel = 310.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle12.getGlobalBounds())) {
        groundlevel = 280.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle13.getGlobalBounds())) {
        groundlevel = 310.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle14.getGlobalBounds())) {
        groundlevel = 360.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else {
        groundlevel = 1000.0f;
        if (!isJumping && !isfalling) {
            isFallingFast = true;
            fastFallVelocity = 0.0f;
        }
    }

    window.setView(view);
    if (showready) {
        fadeinSound.play();
        readyanimationtimer++;
        if (readyanimationtimer >= readyanimationspeed) {
            readyindx++;
            readyanimationtimer = 0;
            if (readyindx >= 12) {
                readyindx = 11;
            }
        }
        readysprite.setTextureRect(IntRect(readyindx * 76, 0, 76, 63));
        if (readyclock.getElapsedTime().asSeconds() >= readyduration) {
            showready = false;
            if (!falldone) {
                isfalling = true;
                falldone = true;
            }
        }
        return;
    }

    if (isfalling) {
        velocityY += gravityfall;
        megamansprite.move(0, velocityY);
        float currentY = megamansprite.getPosition().y;



        if (currentY < groundlevel - 100) {
            megamansprite.setTexture(megamanFall);
            megamansprite.setTextureRect(IntRect(0, 0, 71, 92));
            Fallindx = 1;
            falltimer = 0;
        }
        else if (currentY >= groundlevel - 100 && currentY < groundlevel) {
            falltimer++;
            if (falltimer >= 2) {
                Fallindx++;
                if (Fallindx >= 8) Fallindx = 1;
                falltimer = 0;
            }
            megamansprite.setTexture(megamanFall);
            megamansprite.setTextureRect(IntRect(Fallindx * 71, 0, 71, 92));
        }

        if (currentY + velocityY >= groundlevel) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            isfalling = false;
            velocityY = 0;
            Fallindx = 0;
            megamansprite.setTexture(megamanIdle);
            megamansprite.setTextureRect(IntRect(0, 0, 74, 78));
        }
        return;
    }
    else {
        if (isJumping) {
            velocityY += gravity;
            megamansprite.move(0, velocityY);
            if (megamansprite.getPosition().y >= groundlevel) {
                megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
                isJumping = false;
            }
        }
    }

    if (isFallingFast) {
        fastFallVelocity += fastFallGravity;
        megamansprite.move(0, fastFallVelocity);
        float currentY = megamansprite.getPosition().y;

        megamansprite.setTexture(megamanJump);
        Jumpindx = 4;
        megamansprite.setTextureRect(IntRect(Jumpindx * 68, 0, 68, 90));

        // Check collision with rectangle_forbroken during fast fall
        if (playerCollider.getGlobalBounds().intersects(rectangle_forbroken.getGlobalBounds())) {
            groundlevel = 510.0f - (playerCollider.getGlobalBounds().height / 2.0f) + 22.5f; // Adjust for collider offset
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            isFallingFast = false;
            fastFallVelocity = 0.0f;
            isfalling = false;
            isOnPlatform = true;
            megamansprite.setTexture(megamanIdle);
            megamansprite.setTextureRect(IntRect(0, 0, 74, 78));
            cout << "Landed on rectangle_forbroken during fast fall: Health = " << Health << ", Y = " << megamansprite.getPosition().y << endl;
            return;
        }
        if (playerCollider.getGlobalBounds().intersects(rectangle_forbroken4.getGlobalBounds())) {
            groundlevel = 510.0f - (playerCollider.getGlobalBounds().height / 2.0f) + 22.5f; // Adjust for collider offset
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            isFallingFast = false;
            fastFallVelocity = 0.0f;
            isfalling = false;
            isOnPlatform = true;
            megamansprite.setTexture(megamanIdle);
            megamansprite.setTextureRect(IntRect(0, 0, 74, 78));
            cout << "Landed on rectangle_forbroken during fast fall: Health = " << Health << ", Y = " << megamansprite.getPosition().y << endl;
            return;
        }

        if (currentY + fastFallVelocity >= groundlevel) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            isFallingFast = false;
            fastFallVelocity = 0.0f;
            if (groundlevel >= 600.0f) { // Only die if falling into a pit
                Health = 0;
                megaManDead = true;
            }
            megamansprite.setTexture(megamanIdle);
            megamansprite.setTextureRect(IntRect(0, 0, 74, 78));
        }
        return;
    }
    float minX = 0;
    float maxX = 6651 - (megamansprite.getGlobalBounds().width / 4);
    Vector2f playerPos = megamansprite.getPosition();
    if (playerPos.x < minX) playerPos.x = minX;
    if (playerPos.x > maxX) playerPos.x = maxX;
    megamansprite.setPosition(playerPos.x, playerPos.y);

    ismoving = false;
    if (isfalling) return;

    PlayerMovement();
    Shooting();
    HandelingBullets();
    MegaManHealth();
    // Transition to GAME_OVER if player is dead
    if (megamansprite.getPosition().y >= 1000) {
        gameState = GAME_OVER;
        menuSelection = 0;
    }
    if (megaManDead) {
        gameState = GAME_OVER;
        menuSelection = 0;
    }
    if (finalBoss.isdead && gameState == PLAYING) {
        gameState = WIN_STATE;
        winMusic.play();
        winClock.restart();
        initializeConfetti();
        stageMusic.stop();
        menusound.stop();
        losesound.stop();
    }
}
void initializeConfetti() {
    confettiParticles.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disX(view.getCenter().x - 400, view.getCenter().x + 400);
    uniform_real_distribution<> disY(view.getCenter().y - 300, view.getCenter().y + 300);
    uniform_real_distribution<> disVel(-50, 50);
    uniform_real_distribution<> disLife(1.5f, 3.0f);

    for (int i = 0; i < 50; ++i) {
        Confetti c;
        c.sprite.setTexture(confettiTexture);
        c.sprite.setTextureRect(IntRect(0, 0, confettiFrameWidth, confettiFrameHeight));
        c.sprite.setScale(1.0f, 1.0f);
        c.sprite.setPosition(disX(gen), disY(gen));
        c.velocity = Vector2f(disVel(gen), 100.0f);
        c.lifetime = disLife(gen);
        c.active = true;
        confettiParticles.push_back(c);
    }
    cout << "Initialized " << confettiParticles.size() << " confetti particles." << endl;
}

void updateConfetti(float deltaTime) {
    for (auto& c : confettiParticles) {
        if (!c.active) continue;

        c.timer += deltaTime;
        if (c.timer >= confettiAnimationSpeed) {
            c.frame = (c.frame + 1) % confettiFrameCount;
            c.timer = 0;
            c.sprite.setTextureRect(IntRect(c.frame * confettiFrameWidth, 0, confettiFrameWidth, confettiFrameHeight));
        }

        c.sprite.move(c.velocity * deltaTime);
        c.lifetime -= deltaTime;
        if (c.lifetime <= 0 || c.sprite.getPosition().y > view.getCenter().y + 300) {
            c.active = false;
        }
    }

    confettiParticles.erase(
        remove_if(confettiParticles.begin(), confettiParticles.end(), [](const Confetti& c) { return !c.active; }),
        confettiParticles.end()
    );
}

void Draw()
{
    window.clear();
    window.setView(window.getDefaultView());
    window.draw(backgroundSprite);
    window.setView(view);

    if (isplayer) {
        window.draw(map2);
    }
    else {
        window.draw(mapSprite);
    }
    if (isTallNotBrokenVisible) {
        window.draw(tall_notbroken);
    }
    if (isTall4visible) {
        window.draw(tall_notbroken2);
    }
    window.draw(climbing_area);
    window.draw(climbing2_area);
    window.draw(carSprite2);

    for (int i = 0; i < 5; i++) {
        if (!healthUps[i].gotHealthUp) {
            window.draw(healthUps[i].sprite);
        }
    }
    for (auto& bullet : bullets) {
        window.draw(bullet.sprite);
        if (bullet.isStrong && bullet.frame < 5) {
            window.draw(chargingSprite);
        }
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (!enemies[i].isdead) {
            window.draw(enemies[i].sprite);
        }
    }

    for (int i = 0; i < MONSTER_COUNT; i++) {
        if (!monsters[i].isdead) {
            window.draw(monsters[i].sprite);
        }
    }

    if (!finalBoss.isdead) {
        window.draw(finalBoss.sprite);
        // Draw collider for debugging (remove after testing)
        //window.draw(finalBoss.EnemyCollider);
    }

    for (int i = 0; i < BOSS_COUNT; i++) {
        if (!bosses[i].isdead && !bosses[i].isdying) {
            window.draw(bosses[i].sprite);
        }
        if (bosses[i].isdead || bosses[i].isdying) {
            window.draw(bossDeath[i]);
        }
    }

    for (int i = 0; i < Flying_count; i++) {
        if (!flyingBot[i].isdead) {
            window.draw(flyingBot[i].sprite);
        }
    }

    for (int i = 0; i < ATTACK_COUNT; i++) {
        if (!attack[i].isdead) {
            window.draw(attack[i].sprite);
        }
    }

    for (int i = 0; i < fly_count; i++) {
        if (!Fly[i].isdead) {
            window.draw(Fly[i].sprite);
        }
    }

    if (showready) {
        window.draw(readysprite);
    }
    else if (!megaManDead) {
        window.draw(megamansprite);
    }

    for (auto& bullete : bulletsenemy) {
        if (bullete.active) {
            window.draw(bullete.sprite);
        }
    }

    for (auto& bossBullet : bossBullets) {
        if (bossBullet.bossActive) {
            window.draw(bossBullet.bossSprite);
        }
    }

    for (auto& bomb : bombs) {
        if (bomb.active) {
            window.draw(bomb.sprite);
        }
    }

    for (const auto& explosion : explosions) {
        if (explosion.active) {
            window.draw(explosion.sprite);
        }
    }
    for (auto& c : confettiParticles) {
        if (c.active) {
            window.draw(c.sprite);
        }
    }
    window.draw(carSprite);
    window.draw(trackSprite);
    window.setView(window.getDefaultView());
    window.draw(Health_Bar);
}

void ShootBulletenemy(Vector2f position, int enemyIndex)
{
    BulletEnemy bullete;
    bullete.sprite.setTexture(bulletenemyTexture);
    bullete.sprite.setTextureRect(IntRect(0, 0, bulletenemyFrameWidth, bulletenemyFrameHeight));
    bullete.sprite.setScale(1.0f, 1.0f);
    bullete.velocityX = bulletenemySpeed;
    bullete.active = true;

    // Position bullet based on enemy index
    if (enemyIndex == 0) {
        bullete.sprite.setPosition(position.x + 34.481f, 289.825f); // Enemy 0: x = 734.481, y = 289.825
    }
    else if (enemyIndex == 1) {
        bullete.sprite.setPosition(position.x + 33.09f, 275.95f); // Enemy 1: x = 1433.09, y = 275.95
    }
    else if (enemyIndex == 2) {
        bullete.sprite.setPosition(position.x + 45.18f, 274.1f); // Enemy 2: x = 2145.18, y = 274.1
    }
    else if (enemyIndex == 3) {
        bullete.sprite.setPosition(position.x + 49.18f, 274.1f); // Enemy 3: x = 2849.18, y = 274.1
    }
    else if (enemyIndex == 4) {
        bullete.sprite.setPosition(position.x + 45.23f, 307.729f); // Enemy 4: x = 3545.23, y = 307.729
    }

    bulletsenemy.push_back(bullete);
}

void UpdateBulletsenemy()
{
    for (auto& bullete : bulletsenemy) {
        if (!bullete.active) continue;

        // Update position
        bullete.sprite.move(bullete.velocityX * deltaTime, 0);

        // Deactivate if off-screen
        if (bullete.sprite.getPosition().x < 0 || bullete.sprite.getPosition().x > 6651) {
            bullete.active = false;
        }
    }

    // Remove inactive bullets
    bulletsenemy.erase(
        remove_if(bulletsenemy.begin(), bulletsenemy.end(), [](const BulletEnemy& b) { return !b.active; }),
        bulletsenemy.end()
    );
}

void bossShootBullet(Vector2f bossPosition, int bossIndex)
{
    bossBullet bossBullet;
    bossBullet.bossSprite.setTexture(BossBulletTexture);
    bossBullet.bossSprite.setTextureRect(IntRect(0, 0, bossBulletFrameWidth, bossBulletFrameHeight));
    bossBullet.bossSprite.setScale(1.0f, 1.0f);
    bossBullet.bossSprite.setOrigin(bossBulletFrameWidth / 2.0f, bossBulletFrameHeight / 2.0f);

    // Use bosses[bossIndex] instead of 'boss'
    float mouthOffsetX = 60.5f; // 181/2 * 1.1
    float mouthOffsetY = 92.2f; // 141*0.2 * 1.1
    float scaleX = bosses[bossIndex].sprite.getScale().x; // Use the specific boss
    float scaleY = bosses[bossIndex].sprite.getScale().y;
    float adjustedMouthX = bossPosition.x + (mouthOffsetX * scaleX);
    float adjustedMouthY = bossPosition.y + (mouthOffsetY * scaleY);
    bossBullet.bossSprite.setPosition(adjustedMouthX, adjustedMouthY);

    // Set velocities
    bossBullet.boosVelocityX = bossBulletSpeed; // e.g., -600.0f for left
    bossBullet.bossVelocityY = 700.0f;

    bossBullet.hitbox.setSize(Vector2f(30.0f, 30.0f));
    bossBullet.hitbox.setOrigin(10.0f, 10.0f);
    bossBullet.hitbox.setPosition(bossBullet.bossSprite.getPosition());

    bossBullet.bossActive = true;
    bossBullet.bossIndex = bossIndex;
    bossBullets.push_back(bossBullet);

    // Remove or adjust the isFired block as it seems incomplete
    if (isFired) {
        bossBullet.bossVelocityY += gravity * deltaTime;
        Vector2f position = bossBullet.bossSprite.getPosition();
        position.x += bossBullet.boosVelocityX * deltaTime * 60.f; // Fixed typo: bossPosition -> position
        position.y += bossBullet.bossVelocityY * deltaTime * 60.f;
        bossBullet.bossSprite.setPosition(position);

        float rotation = std::atan2(bossBullet.bossVelocityY, bossBullet.boosVelocityX) * 180.f / 3.14159f;
        bossBullet.bossSprite.setRotation(rotation);

        if (position.y > 550.f) {
            isFired = false;
            bossBullet.bossSprite.setPosition(100.f, 500.f);
            bossBullet.bossVelocityY = -10.f * std::sin(angle * 3.14159f / 180.f);
            bossBullet.bossSprite.setRotation(0);
        }
    }
}

void BossUpdateBullets()
{
    for (auto& bossBullet : bossBullets) {
        if (!bossBullet.bossActive) continue;

        // Deactivate bullet if its boss is dead or dying
        if (bossBullet.bossIndex >= 0 && bossBullet.bossIndex < BOSS_COUNT &&
            (bosses[bossBullet.bossIndex].isdead || bosses[bossBullet.bossIndex].isdying)) {
            bossBullet.bossActive = false;
            continue;
        }

        // Update bullet position
        bossBullet.bossSprite.move(bossBullet.boosVelocityX * deltaTime, bossBullet.bossVelocityY * deltaTime);
        bossBullet.hitbox.setPosition(bossBullet.bossSprite.getPosition());

        // Get bullet position
        float bulletX = bossBullet.bossSprite.getPosition().x;
        float bulletY = bossBullet.bossSprite.getPosition().y;

        // Deactivate if colliding with specific areas
        if (bulletX >= 2379 && bulletX <= 2379 + 400 && bulletY >= 300.0f) {
            bossBullet.bossActive = false;
        }
        else if (bulletX >= 2941.34 && bulletX <= 2941.34 + 477 && bulletY >= 332.0f) {
            bossBullet.bossActive = false;
        }
        // Deactivate if off-screen
        else if (bulletX < 0 || bulletX > 6651 || bulletY > 720) {
            bossBullet.bossActive = false;
        }
    }

    // Remove inactive bullets
    bossBullets.erase(
        remove_if(bossBullets.begin(), bossBullets.end(), [](const bossBullet& b) { return !b.bossActive; }),
        bossBullets.end()
    );
}

void PlayerMovement()
{
    if (megamandamaged || megaManDead)
        return;

    bool pressingX = Keyboard::isKeyPressed(Keyboard::X);
    bool pressingC = Keyboard::isKeyPressed(Keyboard::C);
    bool pressingD = Keyboard::isKeyPressed(Keyboard::D);
    bool pressingA = Keyboard::isKeyPressed(Keyboard::A);
    bool pressingSpace = Keyboard::isKeyPressed(Keyboard::Space);

    // Shoot + Jump
    if ((pressingC || pressingX) && isJumping) {
        float currentY = megamansprite.getPosition().y;
        int frameIndex;
        velocityY += gravity;
        megamansprite.move(0, velocityY);
        if (pressingD) {
            megamansprite.move(4, 0);
            megamansprite.setScale(1, 1);
        }
        else if (pressingA) {
            megamansprite.move(-4, 0);
            megamansprite.setScale(-1, 1);
        }
        if (currentY < groundlevel - 100) {
            frameIndex = jumpstate[3];
        }
        else if (currentY < groundlevel - 50) {
            frameIndex = jumpstate[4];
        }
        else {
            jumpshootanimationtimer++;
            if (jumpshootanimationtimer >= jumpshootspeed) {
                JumpShootindx++;
                if (JumpShootindx >= jumpShootFramesCount) JumpShootindx = 2;
                jumpshootanimationtimer = 0;
            }
            frameIndex = jumpstate[JumpShootindx];
        }
        megamansprite.setTexture(megamanJumpShoot);
        megamansprite.setTextureRect(IntRect(frameIndex * 71.7142857143, 0, 71.7142857143, 89));
        return;
    }
    // Shoot + Run
    else if ((pressingC || pressingX) && (pressingD || pressingA)) {
        ismoving = true;
        if (pressingD) {
            megamansprite.setScale(1, 1);
            megamansprite.move(4, 0);
        }
        else {
            megamansprite.setScale(-1, 1);
            megamansprite.move(-4, 0);
        }
        shootrunanimationtimer++;
        if (shootrunanimationtimer >= shootrunanimationspeed) {
            megamansprite.setTexture(megamanShootRun);
            megamansprite.setTextureRect(IntRect(ShootRunindx * 74.9, 0, 74.9, 78));
            ShootRunindx = (ShootRunindx + 1) % 11;
            shootrunanimationtimer = 0;
        }
        return;
    }
    // Shoot Only
    if (pressingC || pressingX) {
        shooting = true;
        shootanimationtimer++;
        if (shootanimationtimer >= shootanimationspeed && Shootindx < 1) {
            Shootindx++;
            shootanimationtimer = 0;
        }
        megamansprite.setTexture(megamanShoot);
        megamansprite.setTextureRect(IntRect(Shootindx * 73, 0, 73, 79));
        return;
    }
    // Jumping
    if (pressingSpace && !isJumping && !isfalling) {
        isJumping = true;
        velocityY = jumpStrength;
        megamansprite.setTexture(megamanJump);
        megamansprite.setTextureRect(IntRect(0, 0, 68, 90));
        Jumpindx = 0;
        jumpanimationtimer = 0;
        jumpSound.play();
    }
    if (isJumping) {
        velocityY += gravity;
        if (pressingD) {
            megamansprite.move(4, 0);
            megamansprite.setScale(1, 1);
        }
        else if (pressingA) {
            megamansprite.move(-4, 0);
            megamansprite.setScale(-1, 1);
        }
        megamansprite.move(0, velocityY);
        if (Jumpindx < 4) {
            jumpanimationtimer++;
            if (jumpanimationtimer >= jumpanimationspeed) {
                Jumpindx++;
                jumpanimationtimer = 0;
            }
        }
        else if (Jumpindx == 4) {
            megamansprite.setTexture(megamanJump);
            megamansprite.setTextureRect(IntRect(4, 0, 68, 90));
        }
        else if (megamansprite.getPosition().y >= groundlevel - nearGroundThreshold) {
            jumpanimationtimer++;
            if (jumpanimationtimer >= jumpanimationspeed && Jumpindx < 7) {
                Jumpindx++;
                jumpanimationtimer = 0;
            }
        }
        megamansprite.setTexture(megamanJump);
        megamansprite.setTextureRect(IntRect(Jumpindx * 68, 0, 68, 90));
        if (megamansprite.getPosition().y >= groundlevel) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            isJumping = false;
        }
        return;
    }
    // Running
    if (pressingD || pressingA) {
        ismoving = true;
        if (pressingD) {
            megamansprite.setScale(1, 1);
            megamansprite.move(4, 0);
        }
        else {
            megamansprite.setScale(-1, 1);
            megamansprite.move(-4, 0);
        }
        runanimationtimer++;
        if (runanimationtimer >= runanimationspeed) {
            runanimationtimer = 0;
            megamansprite.setTexture(megamanRun);
            megamansprite.setTextureRect(IntRect(Runindx * 67, 0, 67, 77));
            Runindx = (Runindx + 1) % 11;
        }
        return;
    }
    // Idle
    if (shootfinished) {
        megamansprite.setTexture(megamanShoot);
        megamansprite.setTextureRect(IntRect(0, 0, 73, 79));
        shootfinished = false;
    }
    else {
        megamansprite.setTexture(megamanIdle);
        megamansprite.setTextureRect(IntRect(Idleindx * 74, 0, 74, 78));
    }
}

void Start_Enemies() {
    enemiesTex.loadFromFile("C:/SFML Template/Mega Man X material/spritesheet_100.png");
    float enemiesY[ENEMY_COUNT] = { 230,215,213,217,248 };
    for (int i = 0; i < ENEMY_COUNT; i++) {
        enemies[i].sprite.setTexture(enemiesTex);
        enemies[i].sprite.setTextureRect(IntRect(0, 0, 106, 114));
        enemies[i].sprite.setScale(0.9f, 0.9f);
        enemies[i].sprite.setPosition(700 + i * 700, enemiesY[i]);
        enemies[i].frame = 0;
        enemies[i].direction = 1;
        enemies[i].EnemyCollider.setSize(Vector2f(30, 60));
        enemies[i].EnemyCollider.setPosition(enemies[i].sprite.getPosition());
        enemies[i].EnemyCollider.setOrigin(enemies[i].EnemyCollider.getLocalBounds().width - 62, enemies[i].EnemyCollider.getLocalBounds().height - 85);
        enemies[i].EnemyCollider.setFillColor(Color::Black);
        enemies[i].Health = 14;
        enemies[i].Damage = 2;
    }

    FLYING_BOT.loadFromFile("C:/SFML Template/Mega Man X material/spritesheet_13.png");
    float flyingY[Flying_count] = { 220,220,220,210,200 };
    for (int i = 0; i < Flying_count; i++) {
        flyingBot[i].sprite.setTexture(FLYING_BOT);
        flyingBot[i].sprite.setTextureRect(IntRect(0, 0, 70.7, 75));
        flyingBot[i].sprite.setPosition(1300 + i * 700, flyingY[i]);
        flyingBot[i].sprite.setScale(0.9f, 0.9f);
        flyingBot[i].sprite.setOrigin(flyingBot[i].sprite.getLocalBounds().width / 2, flyingBot[i].sprite.getLocalBounds().height / 2);
        flyingBot[i].frame = 0;
        flyingBot[i].direction = 1;
        flyingBot[i].velocity = Vector2f(0, 0);
        flyingBot[i].EnemyCollider.setSize(Vector2f(23, 30));
        flyingBot[i].EnemyCollider.setPosition(flyingBot[i].sprite.getPosition());
        flyingBot[i].EnemyCollider.setOrigin(flyingBot[i].EnemyCollider.getLocalBounds().width - 13, flyingBot[i].EnemyCollider.getLocalBounds().height - 10);
        flyingBot[i].EnemyCollider.setFillColor(Color::Blue);
        flyingBot[i].Health = 6;
        flyingBot[i].Damage = 2;

    }

    Monster1.loadFromFile("C:/SFML Template/Mega Man X material/MONSTER.png");
    for (int i = 0; i < MONSTER_COUNT; i++) {
        float monsterY[MONSTER_COUNT] = { 243,237,273 };
        monsters[i].sprite.setTexture(Monster1);
        monsters[i].sprite.setTextureRect(IntRect(0, 0, 161, 100));
        monsters[i].sprite.setScale(-0.7f, 0.7f);
        monsters[i].sprite.setPosition(2500 + i * 1700, monsterY[i]);
        monsters[i].frame = 0;
        monsters[i].direction = 1;
        monsters[i].EnemyCollider.setSize(Vector2f(50, 40));
        monsters[i].EnemyCollider.setPosition(monsters[i].sprite.getPosition());
        monsters[i].EnemyCollider.setOrigin(monsters[i].EnemyCollider.getLocalBounds().width + 30, monsters[i].EnemyCollider.getLocalBounds().height - 60);
        monsters[i].EnemyCollider.setFillColor(Color::Black);
        monsters[i].Health = 10;
        monsters[i].Damage = 2;
    }

    big_boss.loadFromFile("C:/SFML Template/Mega Man X material/BIGBOSS.png");

    Vector2f bossPositions[BOSS_COUNT] = { {2620, 145}, {3300, 160} }; // Positions for the two bosses
    for (int i = 0; i < BOSS_COUNT; i++) {
        bosses[i].sprite.setTexture(big_boss);
        bosses[i].sprite.setTextureRect(IntRect(0, 0, 181, 141));
        bosses[i].sprite.setScale(1.1f, 1.1f);
        bosses[i].sprite.setPosition(bossPositions[i]);
        bosses[i].EnemyCollider.setSize(Vector2f(100, 90));
        bosses[i].EnemyCollider.setPosition(bosses[i].sprite.getPosition());
        bosses[i].EnemyCollider.setOrigin(bosses[i].EnemyCollider.getLocalBounds().width - 160, bosses[i].EnemyCollider.getLocalBounds().height - 130);
        bosses[i].EnemyCollider.setFillColor(Color::Red);
        bosses[i].Health = 20;
        bosses[i].Damage = 6;
        bosses[i].frame = 0;
        bosses[i].direction = 1;
        bosses[i].isdead = false;
        bosses[i].isdying = false;
        bosses[i].deathFrame = 0;
        bosses[i].deathTimer = 0;

    }



    attacks.loadFromFile("C:/SFML Template/Mega Man X material/spritesheet_11.png");
    float attackY[ATTACK_COUNT] = { 234,250,295,225 };
    for (int i = 0; i < ATTACK_COUNT; i++) {
        attack[i].sprite.setTexture(attacks);
        attack[i].sprite.setTextureRect(IntRect(0, 0, 78, 82));
        attack[i].sprite.setPosition(1000 + i * 1240, attackY[i]);
        attack[i].sprite.setScale(0.8f, 0.8f);
        attack[i].frame = 0;
        attack[i].direction = 1;
        attack[i].EnemyCollider.setSize(Vector2f(20, 20));
        attack[i].EnemyCollider.setPosition(attack[i].sprite.getPosition());
        attack[i].EnemyCollider.setOrigin(attack[i].EnemyCollider.getLocalBounds().width - 42, attack[i].EnemyCollider.getLocalBounds().height - 45);
        attack[i].EnemyCollider.setFillColor(Color::Blue);
        attack[i].Health = 6;
        attack[i].Damage = 2;

    }

    FLY.loadFromFile("C:/SFML Template/Mega Man X material/FLY.png");
    float flyY[fly_count] = { 200,200,200,200,200 };
    for (int i = 0; i < fly_count; i++) {
        Fly[i].sprite.setTexture(FLY);
        Fly[i].sprite.setTextureRect(IntRect(0, 0, 80, 62));
        Fly[i].sprite.setScale(1.2f, 1.2f);
        Fly[i].sprite.setPosition(2100 + i * 500, flyY[i]);
        Fly[i].frame = 0;
        Fly[i].direction = 1;
        Fly[i].EnemyCollider.setSize(Vector2f(23, 50));
        Fly[i].EnemyCollider.setPosition(Fly[i].sprite.getPosition());
        Fly[i].EnemyCollider.setOrigin(Fly[i].EnemyCollider.getLocalBounds().width - 70, Fly[i].EnemyCollider.getLocalBounds().height - 70);
        Fly[i].EnemyCollider.setFillColor(Color::Blue);
        Fly[i].Health = 6;
        Fly[i].Damage = 4;
    }
    // Load FinalBoss Textures
    if (!finalBossIdleTex.loadFromFile("C:/SFML Template/Mega Man X material/finalbossidle.png")) {
        cout << "Failed to load FinalBoss_Idle.png" << endl;
    }
    if (!finalBossSlideTex.loadFromFile("C:/SFML Template/Mega Man X material/finalbossslide.png")) {
        cout << "Failed to load FinalBoss_Slide.png" << endl;
    }
    if (!finalBossWalkTex.loadFromFile("C:/SFML Template/Mega Man X material/finalbosswalk.png")) {
        cout << "Failed to load FinalBoss_Walk.png" << endl;
    }
    if (!finalBossAttackTex.loadFromFile("C:/SFML Template/Mega Man X material/finalbossattack.png")) {
        cout << "Failed to load FinalBoss_Attack.png" << endl;
    }

    // Initialize FinalBoss
    finalBoss.sprite.setTexture(finalBossIdleTex);
    finalBoss.sprite.setTextureRect(IntRect(0, 0, 97, 119));
    finalBoss.sprite.setScale(1.1f, 1.1f);
    finalBoss.sprite.setPosition(6580, 340);
    finalBoss.EnemyCollider.setSize(Vector2f(97, 119)); // Adjusted size to cover sprite
    finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
    finalBoss.EnemyCollider.setOrigin(97 / 5, 119 / 2); // Center the collider (80/2, 100/2)
    finalBoss.EnemyCollider.setFillColor(Color::Red);
    finalBoss.Health = 40;
    finalBoss.Damage = 2;
    finalBoss.sprite.setOrigin(97 / 2, 119 / 2);
    finalBoss.isActive = false;
}

void Update_Enemies() {
    static Clock clock;
    static float delay = 0.2f;
    static float time = 0.1f;
    static Clock clock2;
    Vector2f playerPos = megamansprite.getPosition();

    if (clock2.getElapsedTime().asSeconds() >= time) {
        for (int i = 0; i < Flying_count; i++) {
            if (flyingBot[i].isdying) {
                flyingBot[i].deathTimer += deltaTime * 5;
                if (flyingBot[i].deathTimer >= flyingBot[i].deathAnimationSpeed) {
                    flyingBot[i].deathTimer = 0;
                    flyingBot[i].deathFrame++;
                    if (flyingBot[i].deathFrame >= 7) {
                        flyingBot[i].isdead = true;
                        flyingBot[i].EnemyCollider.setSize(Vector2f(0, 0));
                    }
                    else {
                        flyingBot[i].sprite.setTextureRect(IntRect(flyingBot[i].deathFrame * 74, 0, 74, 72));
                    }
                }
            }

            else if (!flyingBot[i].isdead) {
                Vector2f flyingPosition = flyingBot[i].sprite.getPosition();
                float distance4 = abs(playerPos.x - flyingPosition.x);
                if (distance4 <= 300.0f) {

                    flyingBot[i].velocity = playerPos - flyingPosition;
                    flyingBot[i].velocity = Normalize(flyingBot[i].velocity) * speedf;
                    if (playerPos.x > flyingPosition.x) {
                        flyingBot[i].sprite.setScale(0.9f, 0.9f);
                    }
                    else {
                        flyingBot[i].sprite.setScale(-0.9f, 0.9f);
                    }
                    flyingBot[i].sprite.move(flyingBot[i].velocity);
                    flyingBot[i].EnemyCollider.move(flyingBot[i].velocity);
                    flyingBot[i].sprite.setTextureRect(IntRect(flyingBot[i].frame * 70.7, 0, 70.7, 75));
                    flyingBot[i].frame++;
                    flyingBot[i].frame = flyingBot[i].frame % 10;
                }
            }
            if (flyingBot[0].isdead || flyingBot[0].isdying) {
                Health_Up(flyingBot[0].sprite.getPosition(), megamansprite.getPosition().y, 0);
            }
            if (flyingBot[1].isdead || flyingBot[1].isdying) {
                Health_Up(flyingBot[1].sprite.getPosition(), megamansprite.getPosition().y, 1);
            }
            if (flyingBot[2].isdead || flyingBot[2].isdying) {
                Health_Up(flyingBot[2].sprite.getPosition(), megamansprite.getPosition().y, 2);
            }
            if (flyingBot[3].isdead || flyingBot[3].isdying) {
                Health_Up(flyingBot[3].sprite.getPosition(), megamansprite.getPosition().y, 3);
            }
            if (flyingBot[4].isdead || flyingBot[4].isdying) {
                Health_Up(flyingBot[4].sprite.getPosition(), megamansprite.getPosition().y, 4);
            }
        }

        for (int i = 0; i < ATTACK_COUNT; i++) {
            if (attack[i].isdying) {
                attack[i].deathTimer += deltaTime * 5;
                if (attack[i].deathTimer >= attack[i].deathAnimationSpeed) {
                    attack[i].deathTimer = 0;
                    attack[i].deathFrame++;
                    if (attack[i].deathFrame >= 7) {
                        attack[i].isdead = true;
                        attack[i].EnemyCollider.setSize(Vector2f(0, 0));
                    }
                    else {
                        attack[i].sprite.setTextureRect(IntRect(attack[i].deathFrame * 77, 0, 77, 77));

                    }
                }
            }
            else if (!attack[i].isdead) {
                Vector2f attackPos = attack[i].sprite.getPosition();
                float distance5 = abs(playerPos.x - attackPos.x);
                if (distance5 <= 200.0f) {
                    attack[i].sprite.setTextureRect(IntRect(attack[i].frame * 78, 0, 78, 82));
                    attack[i].frame++;
                    attack[i].frame = attack[i].frame % 3;
                    attack[i].sprite.move(-6.0f, 0.0);
                    attack[i].EnemyCollider.move(-6.0f, 0.0);
                }
            }
        }

        for (int i = 0; i < fly_count; i++) {
            if (Fly[i].isdying) {
                Fly[i].deathTimer += deltaTime * 5;
                if (Fly[i].deathTimer >= Fly[i].deathAnimationSpeed) {
                    Fly[i].deathTimer = 0;
                    Fly[i].deathFrame++;
                    if (Fly[i].deathFrame >= 7) {
                        Fly[i].isdead = true;
                        Fly[i].EnemyCollider.setSize(Vector2f(0, 0));
                    }
                    else {
                        Fly[i].sprite.setTextureRect(IntRect(Fly[i].deathFrame * 74, 0, 74, 72));
                    }
                }
            }
            else if (!Fly[i].isdead) {
                Vector2f flyPosition = Fly[i].sprite.getPosition();
                float distance3 = abs(playerPos.x - flyPosition.x);
                if (distance3 <= 150.0f) {
                    int prevFrame = Fly[i].frame;
                    Fly[i].sprite.setTextureRect(IntRect(80 * Fly[i].frame, 0, 80, 62));
                    Fly[i].frame++;
                    Fly[i].frame = Fly[i].frame % 9;
                    Fly[i].sprite.move(-1.0f, 0);
                    Fly[i].EnemyCollider.move(-1.0f, 0);
                    if (prevFrame == 7 && Fly[i].frame == 8) {
                        ShootBomb(flyPosition);
                    }
                }
            }
        }

        for (int i = 0; i < BOSS_COUNT; i++) {
            if (bosses[0].isdying || bosses[0].isdead) {
                if (bossDeath[0].getPosition().y == 550) {
                    bossDeath[0].move(0.0f, 0.0f);
                }
                else {
                    bossDeath[0].move(0.0f, 55.0f);
                }
            }
            if (bosses[1].isdying || bosses[1].isdead) {
                if (bossDeath[1].getPosition().y == 550) {
                    bossDeath[1].move(0.0f, 0.0f);
                }
                else {
                    bossDeath[1].move(0.0f, 55.0f);
                }
            }
            else if (!bosses[i].isdead && !bosses[i].isdying) { // Prevent bullet spawning if dead or dying
                Vector2f bossPosition = bosses[i].sprite.getPosition();
                float distance2 = abs(playerPos.x - bossPosition.x);
                if (distance2 <= 300.0f) {
                    bosses[i].sprite.setTextureRect(IntRect(bosses[i].frame * 181, 0, 181, 141));
                    bosses[i].frame++;
                    bosses[i].frame = bosses[i].frame % 6;
                    bosses[i].sprite.move(0.0f, 0);
                    bosses[i].EnemyCollider.move(0.0f, 0);
                    bossShootBullet(bossPosition, i); // Pass the boss index
                }
            }
        }

        clock2.restart();
    }

    if (clock.getElapsedTime().asSeconds() >= delay) {

        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (enemies[i].isdying) {
                enemies[i].deathTimer += deltaTime * 5;
                if (enemies[i].deathTimer >= enemies[i].deathAnimationSpeed) {
                    enemies[i].deathTimer = 0;
                    enemies[i].deathFrame++;

                    if (enemies[i].deathFrame >= 7) {
                        enemies[i].isdead = true;
                        enemies[i].EnemyCollider.setSize(Vector2f(0, 0));
                    }
                    else {
                        enemies[i].sprite.setTextureRect(IntRect(enemies[i].deathFrame * 74, 0, 74, 72));
                    }
                }
            }
            else if (!enemies[i].isdead) {
                Vector2f enemiesPosition = enemies[i].sprite.getPosition();
                float distance1 = abs(playerPos.x - enemiesPosition.x);
                if (distance1 <= 100.0f) {
                    enemies[i].sprite.setTextureRect(IntRect(106 * enemies[i].frame, 0, 106, 114));
                    int prevFrame = enemies[i].frame;
                    enemies[i].frame += enemies[i].direction;
                    if (enemies[i].frame == 12 && prevFrame == 11) {
                        // Shoot bullet when reaching frame 12 (final frame before direction change)
                        ShootBulletenemy(enemiesPosition, i);
                    }
                    if (enemies[i].frame == 12)
                        enemies[i].direction = -1;
                    else if (enemies[i].frame == 0)
                        enemies[i].direction = 1;
                }

            }
        }



        for (int i = 0; i < MONSTER_COUNT; i++) {
            if (monsters[i].isdying) {
                monsters[i].deathTimer += deltaTime * 6;
                if (monsters[i].deathTimer >= monsters[i].deathAnimationSpeed) {
                    monsters[i].deathTimer = 0;
                    monsters[i].deathFrame++;

                    if (monsters[i].deathFrame >= 7) {
                        monsters[i].isdead = true;
                        monsters[i].EnemyCollider.setSize(Vector2f(0, 0));
                    }
                    else {
                        monsters[i].sprite.setTextureRect(IntRect(monsters[i].deathFrame * 74, 0, 74, 72));
                    }
                }
            }
            else if (!monsters[i].isdead) {
                monsters[i].sprite.setTextureRect(IntRect(161 * monsters[i].frame, 0, 161, 100));
                monsters[i].frame += monsters[i].direction;
                if (monsters[i].frame == 3)
                    monsters[i].direction = -1;
                else if (monsters[i].frame == 0)
                    monsters[i].direction = 1;
            }
        }
        clock.restart();

    }
    // Update FinalBoss
    if (finalBoss.isdying) {
        finalBoss.deathTimer += deltaTime * 5;
        if (finalBoss.deathTimer >= finalBoss.deathAnimationSpeed) {
            finalBoss.deathTimer = 0;
            finalBoss.deathFrame++;
            if (finalBoss.deathFrame >= 7) {
                finalBoss.isdead = true;
                finalBoss.EnemyCollider.setSize(Vector2f(0, 0));
            }
            else {
                finalBoss.sprite.setTexture(dieEffect);
                finalBoss.sprite.setTextureRect(IntRect(finalBoss.deathFrame * 74, 0, 74, 72));
                finalBoss.EnemyCollider.setSize(Vector2f(54, 72));
                finalBoss.EnemyCollider.setOrigin(54 / 2, 72 / 2);
                finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
            }
        }
    }
    else if (!finalBoss.isdead) {
        Vector2f playerPos = megamansprite.getPosition();
        Vector2f bossPos = finalBoss.sprite.getPosition();
        float distance = sqrt(pow(playerPos.x - bossPos.x, 2) + pow(playerPos.y - bossPos.y, 2));

        const float activationRange = 300.0f;
        const float deactivationRange = 500.0f;

        if (distance <= activationRange) {
            finalBoss.isActive = true;
        }
        else if (distance > deactivationRange) {
            finalBoss.isActive = false;
            finalBoss.isIdle = true;
            finalBoss.isSliding = false;
            finalBoss.isWalking = false;
            finalBoss.isAttacking = false;
            finalBoss.timer = 0.0f;
            finalBoss.frame = 0;
            finalBoss.speed = 2.0f;
        }

        if (!finalBoss.isActive) {
            finalBoss.sprite.setTexture(finalBossIdleTex);
            finalBoss.sprite.setTextureRect(IntRect(0, 0, 97, 116));
            finalBoss.sprite.setOrigin(97 / 2, 116 / 2);
            finalBoss.EnemyCollider.setSize(Vector2f(77, 116));
            finalBoss.EnemyCollider.setOrigin(77 / 2, 116 / 2);
            if (playerPos.x > bossPos.x) {
                finalBoss.sprite.setScale(1.1f, 1.1f);
            }
            else {
                finalBoss.sprite.setScale(-1.1f, 1.1f);
            }
            finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
        }
        else {
            if (playerPos.x > bossPos.x) {
                finalBoss.direction = 1;
                finalBoss.sprite.setScale(1.1f, 1.1f);
            }
            else {
                finalBoss.direction = -1;
                finalBoss.sprite.setScale(-1.1f, 1.1f);
            }

            if (finalBoss.isIdle) {
                finalBoss.timer += deltaTime;
                finalBoss.sprite.setTexture(finalBossIdleTex);
                finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 97, 0, 97, 116));
                finalBoss.sprite.setOrigin(97 / 2, 116 / 2);
                finalBoss.EnemyCollider.setSize(Vector2f(77, 116));
                finalBoss.EnemyCollider.setOrigin(77 / 2, 116 / 2);
                finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
                finalBoss.frame = (finalBoss.frame + 1) % 4;
                if (finalBoss.timer >= 3.0f) {
                    finalBoss.isIdle = false;
                    finalBoss.isSliding = true;
                    finalBoss.timer = 0;
                    finalBoss.speed = 5.0f;
                }
            }
            else if (finalBoss.isSliding) {
                finalBoss.sprite.setTexture(finalBossSlideTex);
                finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 57, 0, 57, 76));
                finalBoss.sprite.setOrigin(57 / 2, 76 / 2);
                finalBoss.EnemyCollider.setSize(Vector2f(37, 76));
                finalBoss.EnemyCollider.setOrigin(37 / 2, 76 / 2);
                finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
                finalBoss.frame = (finalBoss.frame + 1) % 1;
                finalBoss.sprite.move(finalBoss.direction * finalBoss.speed, 0);
                finalBoss.EnemyCollider.move(finalBoss.direction * finalBoss.speed, 0);
                if (distance <= 300.0f) {
                    finalBoss.isSliding = false;
                    finalBoss.isWalking = true;
                    finalBoss.speed = 2.0f;
                }
            }
            else if (finalBoss.isWalking) {
                finalBoss.sprite.setTexture(finalBossWalkTex);
                finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 98, 0, 98, 122));
                finalBoss.sprite.setOrigin(98 / 2, 122 / 2);
                finalBoss.EnemyCollider.setSize(Vector2f(78, 122));
                finalBoss.EnemyCollider.setOrigin(78 / 2, 122 / 2);
                finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
                finalBoss.frame = (finalBoss.frame + 1) % 9;
                finalBoss.sprite.move(finalBoss.direction * finalBoss.speed, 0);
                finalBoss.EnemyCollider.move(finalBoss.direction * finalBoss.speed, 0);
                if (distance <= 50.0f) {
                    finalBoss.isWalking = false;
                    finalBoss.isAttacking = true;
                    finalBoss.speed = 0.0f;
                }
            }
            else if (finalBoss.isAttacking) {
                finalBoss.sprite.setTexture(finalBossAttackTex);
                finalBoss.timer += deltaTime;
                finalBoss.sprite.setOrigin(112 / 2, 118 / 2);
                finalBoss.EnemyCollider.setSize(Vector2f(92, 118));
                finalBoss.EnemyCollider.setOrigin(92 / 2, 118 / 2);
                finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
                const float attackAnimationSpeed = 0.04f;
                if (finalBoss.timer >= attackAnimationSpeed) {
                    finalBoss.timer = 0;
                    finalBoss.frame = (finalBoss.frame + 1) % 3;
                }
                finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 112, 0, 112, 118));
                if (distance > 50.0f) {
                    finalBoss.isAttacking = false;
                    finalBoss.isWalking = true;
                    finalBoss.speed = 2.0f;
                }
            }
        }
    }
}

void Shooting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        facingDirection = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        facingDirection = -1;
    }

    if (shootCooldown > 0.0f) {
        shootCooldown -= deltaTime;
    }

    bool isAnyBulletForming = false;
    for (const auto& bullet : bullets) {
        if (bullet.isStrong && bullet.isForming) {
            isAnyBulletForming = true;
            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        if (!CWasPressed && !XWasPressed && !isAnyBulletForming && shootCooldown <= 0.0f) {
            chargeShootSound.play(); bool soundPlayed = false;
            for (auto& sound : chargeShootSounds) {
                if (sound.getStatus() != Sound::Playing) { // إذا الصوت مش بيتشغل
                    sound.play();
                    soundPlayed = true;
                    break;
                }
            }
            if (!soundPlayed) {
                std::cout << "No available sound slot, skipping play!" << std::endl;
            }
            Bullet b;
            b.bulletCollider.setSize(Vector2f(10, 12));
            chargingSprite.setTexture(chargingTex);
            chargingSprite.setTextureRect(IntRect(0, 0, 40, 40));
            chargingSprite.setScale(1.3, 1.3);
            b.sprite.setTexture(strongBulletTex);
            b.isStrong = true;
            b.damage = 4;
            b.isForming = true;
            b.frame = 0;
            b.sprite.setTextureRect(IntRect(0, 0, 72, 66));
            b.sprite.setScale(0.9f * facingDirection, 0.9f);
            shootCooldown = shootCooldownTime;
            int setX = 1 * facingDirection;
            if (isJumping) {
                if (facingDirection == -1) {
                    b.sprite.setPosition(megamansprite.getPosition().x + setX + 6, megamansprite.getPosition().y - 26);
                    chargingSprite.setPosition(megamansprite.getPosition().x - 18, megamansprite.getPosition().y - 20);
                }
                else {
                    b.sprite.setPosition(megamansprite.getPosition().x - setX - 6, megamansprite.getPosition().y - 26);
                    chargingSprite.setPosition(megamansprite.getPosition().x - 29, megamansprite.getPosition().y - 20);

                }
            }
            else {
                if (facingDirection == -1) {
                    b.sprite.setPosition(megamansprite.getPosition().x + setX - 4, megamansprite.getPosition().y - 26);
                    chargingSprite.setPosition(megamansprite.getPosition().x - 30, megamansprite.getPosition().y - 20);
                }
                else {
                    b.sprite.setPosition(megamansprite.getPosition().x - setX + 8, megamansprite.getPosition().y - 26);
                    chargingSprite.setPosition(megamansprite.getPosition().x - 20, megamansprite.getPosition().y - 20);

                }
            }
            bullets.push_back(b);
            XWasPressed = true;
        }
    }
    else {
        XWasPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        if (!CWasPressed && !XWasPressed && !isAnyBulletForming && shootCooldown <= 0.0f) {
            shootSound.play(); bool soundPlayed = false;
            for (auto& sound : shootSounds) {
                if (sound.getStatus() != Sound::Playing) { // إذا الصوت مش بيتشغل
                    sound.play();
                    soundPlayed = true;
                    break;
                }
            }
            if (!soundPlayed) {
                std::cout << "No available sound slot, skipping play!" << std::endl;
            }
            Bullet b;
            b.bulletCollider.setSize(Vector2f(6, 6));
            b.sprite.setTexture(bulletTex);
            b.isStrong = false;
            b.damage = 2;
            b.isForming = false;
            b.velocity = Vector2f(250 * facingDirection, 0);
            shootCooldown = shootCooldownTime;
            b.sprite.setScale(0.9f * facingDirection, 0.9f);
            int setX = 1 * facingDirection;
            if (isJumping) {
                if (facingDirection == -1) {
                    b.sprite.setPosition(megamansprite.getPosition().x + setX, megamansprite.getPosition().y - 6);
                }
                else {
                    b.sprite.setPosition(megamansprite.getPosition().x - setX, megamansprite.getPosition().y - 6);
                }
            }
            else {
                b.sprite.setPosition(megamansprite.getPosition().x + setX, megamansprite.getPosition().y - 6);
            }
            bullets.push_back(b);
            CWasPressed = true;
        }
    }
    else {
        CWasPressed = false;
    }
}

void HandelingBullets() {
    for (int i = 0; i < bullets.size();) {

        bullets[i].upDate(deltaTime);

        bool bulletHit = false;

        if (bullets[i].isStrong) {
            if (bullets[i].bulletCollider.getPosition().x < megamansprite.getPosition().x - 120 ||
                bullets[i].bulletCollider.getPosition().x > megamansprite.getPosition().x + 178)
            {
                bullets.erase(bullets.begin() + i);
                continue;
            }
        }
        else {
            if (bullets[i].bulletCollider.getPosition().x < megamansprite.getPosition().x - 140 ||
                bullets[i].bulletCollider.getPosition().x > megamansprite.getPosition().x + 140)
            {
                bullets.erase(bullets.begin() + i);
                continue;
            }
        }
        for (int j = 0; j < Flying_count; j++) {
            if (!flyingBot[j].isdead && !flyingBot[j].isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(flyingBot[j].EnemyCollider.getGlobalBounds())) {
                flyingBot[j].Health -= bullets[i].damage;
                if (flyingBot[j].Health <= 0) {
                    flyingBot[j].isdying = true;
                    flyingBot[j].sprite.setTexture(dieEffect);
                    flyingBot[j].sprite.setTextureRect(IntRect(0, 0, 74, 72));
                    flyingBot[j].deathFrame = 0;
                    healthUps[0].sprite.setTexture(healthupTex);
                    healthUps[0].sprite.setTextureRect(IntRect(0, 0, 18, 14));
                    healthUps[0].sprite.setScale(0.8f, 0.8f);
                    healthUps[0].sprite.setPosition(flyingBot[0].sprite.getPosition());
                    healthUps[0].frame = 0;
                    healthUps[1].sprite.setTexture(healthupTex);
                    healthUps[1].sprite.setTextureRect(IntRect(0, 0, 18, 14));
                    healthUps[1].sprite.setScale(0.8f, 0.8f);
                    healthUps[1].sprite.setPosition(flyingBot[1].sprite.getPosition());
                    healthUps[1].frame = 0;
                    healthUps[2].sprite.setTexture(healthupTex);
                    healthUps[2].sprite.setTextureRect(IntRect(0, 0, 18, 14));
                    healthUps[2].sprite.setScale(0.8f, 0.8f);
                    healthUps[2].sprite.setPosition(flyingBot[2].sprite.getPosition());
                    healthUps[2].frame = 0;
                    healthUps[3].sprite.setTexture(healthupTex);
                    healthUps[3].sprite.setTextureRect(IntRect(0, 0, 18, 14));
                    healthUps[3].sprite.setScale(0.8f, 0.8f);
                    healthUps[3].sprite.setPosition(flyingBot[3].sprite.getPosition());
                    healthUps[3].frame = 0;
                    healthUps[4].sprite.setTexture(healthupTex);
                    healthUps[4].sprite.setTextureRect(IntRect(0, 0, 18, 14));
                    healthUps[4].sprite.setScale(0.8f, 0.8f);
                    healthUps[4].sprite.setPosition(flyingBot[4].sprite.getPosition());
                    healthUps[4].frame = 0;
                }
                bulletHit = true;
                break;
            }
        }

        for (int j = 0; j < ENEMY_COUNT; j++) {
            if (!enemies[j].isdead && !enemies[j].isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(enemies[j].EnemyCollider.getGlobalBounds())) {
                enemies[j].Health -= bullets[i].damage;
                if (enemies[j].Health <= 0) {
                    enemies[j].isdying = true;
                    enemies[j].sprite.setTexture(dieEffect);
                    enemies[j].sprite.setTextureRect(IntRect(0, 0, 74, 72));
                    enemies[j].deathFrame = 0;
                }
                bulletHit = true;
                break;
            }
        }


        for (int j = 0; j < MONSTER_COUNT; j++) {
            if (!monsters[j].isdead && !monsters[j].isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(monsters[j].EnemyCollider.getGlobalBounds())) {
                monsters[j].Health -= bullets[i].damage;
                if (monsters[j].Health <= 0) {
                    monsters[j].isdying = true;
                    monsters[j].sprite.setTexture(dieEffect);
                    monsters[j].sprite.setTextureRect(IntRect(0, 0, 74, 72));
                    monsters[j].deathFrame = 0;
                }
                bulletHit = true;
                break;
            }
        }

        for (int j = 0; j < BOSS_COUNT; j++) {
            if (!bosses[j].isdead && !bosses[j].isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(bosses[j].EnemyCollider.getGlobalBounds())) {
                bosses[j].Health -= bullets[i].damage;
                if (bosses[j].Health <= 0) {
                    bosses[j].isdying = true;
                    bossDeath[j].setTexture(bossDeathTex);
                    bossDeath[j].setPosition(bosses[j].sprite.getPosition().x + 10, bosses[j].sprite.getPosition().y);
                    bossDeath[j].setScale(1.1f, 1.4f);
                }
                bulletHit = true;
                break;
            }
        }

        if (!finalBoss.isdead && !finalBoss.isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(finalBoss.EnemyCollider.getGlobalBounds())) {
            finalBoss.Health -= bullets[i].damage;
            if (finalBoss.Health <= 0) {
                finalBoss.isdying = true;
                finalBoss.sprite.setTexture(dieEffect);
                finalBoss.sprite.setTextureRect(IntRect(0, 0, 74, 72));
                finalBoss.deathFrame = 0;
            }
            bulletHit = true;
        }

        for (int j = 0; j < ATTACK_COUNT; j++) {
            if (!attack[j].isdead && !attack[j].isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(attack[j].EnemyCollider.getGlobalBounds())) {
                attack[j].Health -= bullets[i].damage;
                if (attack[j].Health <= 0) {
                    attack[j].isdying = true;
                    attack[j].sprite.setTexture(attackDeathTex);
                    attack[j].deathFrame = 0;
                }
                bulletHit = true;
                break;
            }
        }


        for (int j = 0; j < fly_count; j++) {
            if (!Fly[j].isdead && !Fly[j].isdying && bullets[i].bulletCollider.getGlobalBounds().intersects(Fly[j].EnemyCollider.getGlobalBounds())) {
                Fly[j].Health -= bullets[i].damage;
                if (Fly[j].Health <= 0) {
                    Fly[j].isdying = true;
                    Fly[j].sprite.setTexture(dieEffect);
                    Fly[j].sprite.setTextureRect(IntRect(0, 0, 74, 72));
                    Fly[j].deathFrame = 0;
                }
                bulletHit = true;
                break;
            }
        }


        if (bulletHit) {
            bullets.erase(bullets.begin() + i);
        }
        else {
            i++;
        }
    }
}

void ShootBomb(Vector2f position)
{
    Bomb bomb;
    bomb.sprite.setTexture(bombTexture);
    bomb.sprite.setTextureRect(IntRect(0, 0, bombFrameWidth, bombFrameHeight));
    bomb.sprite.setScale(1.0f, 1.0f);
    bomb.velocityY = bombSpeed;
    bomb.active = true;
    bomb.sprite.setOrigin(bombFrameWidth / 2.0f, bombFrameHeight / 2.0f); // Center the origin

    // Fly sprite height (62 * scale 1.2 = 74.4), so spawn bomb at Fly's bottom
    float flySpriteHeight = 62.0f * 1.2f; // Fly sprite height after scaling
    float bombSpawnY = position.y + flySpriteHeight; // Spawn at bottom of Fly
    float bombSpawnX = position.x + 30.0f; // Add 20 pixels to the right
    bomb.sprite.setPosition(bombSpawnX, bombSpawnY);

    // Set up a larger hitbox (30x30) centered on the sprite
    bomb.hitbox.setSize(Vector2f(30.0f, 30.0f));
    bomb.hitbox.setPosition(bomb.sprite.getPosition().x - 15.0f, bomb.sprite.getPosition().y - 15.0f);
    bomb.hitbox.setOrigin(15.0f, 15.0f);

    bombs.push_back(bomb);
}

void UpdateBombs() {
    Vector2f playerPos = megamansprite.getPosition();
    playerCollider.setPosition(playerPos);

    for (auto& bomb : bombs) {
        if (!bomb.active) continue;

        // Update position (move downward)
        bomb.sprite.move(0, bomb.velocityY * deltaTime);
        bomb.hitbox.setPosition(bomb.sprite.getPosition().x - 15.0f, bomb.sprite.getPosition().y - 15.0f);

        // Check proximity to player
        float distance = sqrt(pow(playerPos.x - bomb.sprite.getPosition().x, 2) + pow(playerPos.y - bomb.sprite.getPosition().y, 2));
        if (distance <= proximityDistance) {
            SpawnExplosion(bomb.sprite.getPosition()); // Spawn explosion when close to player
            DamageMegaMan(2, bomb.sprite.getPosition());
            bomb.active = false;
            continue;
        }

        // Check collision with rectangles to determine ground level
        float bombGroundLevel = 1000.0f; // Default to a high value (pit)
        vector<RectangleShape*> rectangles = {
            &rectangle0, &rectangle1, &rectangle2, &rectangle3, &rectangle_toward3,
            &rectangle_forbroken, &rectangle4, &rectangle_toward4, &rectangle_forbroken4,
            &slantedEdge0, &rectangle5, &rectangle6, &rectangle7, &rectangle8,
            &rectangle9, &rectangle10, &slantedEdge1, &rectangle11, &rectangle12,
            &rectangle13, &rectangle14
        };

        for (auto* rect : rectangles) {
            if (bomb.hitbox.getGlobalBounds().intersects(rect->getGlobalBounds())) {
                if (rect == &rectangle0) bombGroundLevel = 294.0f;
                else if (rect == &rectangle1) bombGroundLevel = 262.5f;
                else if (rect == &rectangle2) bombGroundLevel = 278.0f;
                else if (rect == &rectangle3 && isTallNotBrokenVisible) bombGroundLevel = 282.0f;
                else if (rect == &rectangle_toward3) bombGroundLevel = 282.0f;
                else if (rect == &rectangle_forbroken) bombGroundLevel = 510.0f;
                else if (rect == &rectangle4 && isTall4visible) bombGroundLevel = 315.0f;
                else if (rect == &rectangle_toward4) bombGroundLevel = 315.0f;
                else if (rect == &rectangle_forbroken4) bombGroundLevel = 510.0f;
                else if (rect == &slantedEdge0) {
                    float bombX = bomb.sprite.getPosition().x;
                    float edgeX = slantedEdge0.getPosition().x;
                    float relativeX = bombX - edgeX;
                    float edgeHeight = slantedEdge0.getPosition().y;
                    float slope = tan(14 * 3.1415926535 / 180);
                    bombGroundLevel = edgeHeight - (relativeX * slope);
                }
                else if (rect == &rectangle5) bombGroundLevel = 280.0f;
                else if (rect == &rectangle6) bombGroundLevel = 280.0f;
                else if (rect == &rectangle7) bombGroundLevel = 250.0f;
                else if (rect == &rectangle8) bombGroundLevel = 250.0f;
                else if (rect == &rectangle9) bombGroundLevel = 250.0f;
                else if (rect == &rectangle10) bombGroundLevel = 280.0f;
                else if (rect == &slantedEdge1) {
                    float bombX = bomb.sprite.getPosition().x;
                    float edgeX = slantedEdge1.getPosition().x;
                    float relativeX = bombX - edgeX;
                    float edgeHeight = slantedEdge1.getPosition().y;
                    float slope = tan(165 * 3.1415926535 / 180);
                    bombGroundLevel = edgeHeight - (relativeX * slope);
                }
                else if (rect == &rectangle11) bombGroundLevel = 310.0f;
                else if (rect == &rectangle12) bombGroundLevel = 280.0f;
                else if (rect == &rectangle13) bombGroundLevel = 310.0f;
                else if (rect == &rectangle14) bombGroundLevel = 360.0f;
                break;
            }
        }

        // Stop bomb at ground level (but don’t explode)
        float bombBottom = bomb.sprite.getPosition().y + (bombFrameHeight * bomb.sprite.getScale().y) / 2;
        if (bombBottom >= bombGroundLevel + 50.0f) {
            bomb.sprite.setPosition(bomb.sprite.getPosition().x, bombGroundLevel + 50.0f - (bombFrameHeight * bomb.sprite.getScale().y) / 2);
            bomb.hitbox.setPosition(bomb.sprite.getPosition().x - 15.0f, bomb.sprite.getPosition().y - 15.0f);
            bomb.velocityY = 0; // Stop falling
        }

        // Deactivate if off-screen
        if (bomb.sprite.getPosition().y > 720 + bombFrameHeight) {
            bomb.active = false; 
        }
    }

    
    bombs.erase(
        remove_if(bombs.begin(), bombs.end(), [](const Bomb& b) { return !b.active; }),
        bombs.end()
    );
}

void SpawnExplosion(Vector2f position) {
    Explosion explosion;
    explosion.sprite.setTexture(explosionTexture);
    explosion.sprite.setTextureRect(IntRect(0, 0, explosion.frameWidth, explosion.frameHeight));
    explosion.sprite.setScale(2.0f, 2.0f);
    explosion.sprite.setOrigin(explosion.frameWidth / 2.0f, explosion.frameHeight / 2.0f);
    explosion.sprite.setPosition(position); // Set to exact bomb position
    explosion.active = true;
    explosion.frame = 0;
    explosion.timer = 0;
    explosion.lifetime = 2.0f;
    explosion.velocityY = 0.0f;

    // Set up hitbox (slightly smaller than sprite for precise collision)
    explosion.hitbox.setSize(Vector2f(50.0f, 50.0f));
    explosion.hitbox.setOrigin(25.0f, 25.0f);
    explosion.hitbox.setPosition(position);

    // Determine the ground level based on rectangle collisions
    float explosionGroundLevel = 1000.0f; // Default to a high value (pit)
    vector<RectangleShape*> rectangles = {
        &rectangle0, &rectangle1, &rectangle2, &rectangle3, &rectangle_toward3,
        &rectangle_forbroken, &rectangle4, &rectangle_toward4, &rectangle_forbroken4,
        &slantedEdge0, &rectangle5, &rectangle6, &rectangle7, &rectangle8,
        &rectangle9, &rectangle10, &slantedEdge1, &rectangle11, &rectangle12,
        &rectangle13, &rectangle14
    };

    for (auto* rect : rectangles) {
        if (explosion.hitbox.getGlobalBounds().intersects(rect->getGlobalBounds())) {
            if (rect == &rectangle0) explosionGroundLevel = 294.0f;
            else if (rect == &rectangle1) explosionGroundLevel = 262.5f;
            else if (rect == &rectangle2) explosionGroundLevel = 278.0f;
            else if (rect == &rectangle3 && isTallNotBrokenVisible) explosionGroundLevel = 282.0f;
            else if (rect == &rectangle_toward3) explosionGroundLevel = 282.0f;
            else if (rect == &rectangle_forbroken) explosionGroundLevel = 510.0f;
            else if (rect == &rectangle4 && isTall4visible) explosionGroundLevel = 315.0f;
            else if (rect == &rectangle_toward4) explosionGroundLevel = 315.0f;
            else if (rect == &rectangle_forbroken4) explosionGroundLevel = 510.0f;
            else if (rect == &slantedEdge0) {
                float explosionX = position.x;
                float edgeX = slantedEdge0.getPosition().x;
                float relativeX = explosionX - edgeX;
                float edgeHeight = slantedEdge0.getPosition().y;
                float slope = tan(14 * 3.1415926535 / 180);
                explosionGroundLevel = edgeHeight - (relativeX * slope);
            }
            else if (rect == &rectangle5) explosionGroundLevel = 280.0f;
            else if (rect == &rectangle6) explosionGroundLevel = 280.0f;
            else if (rect == &rectangle7) explosionGroundLevel = 250.0f;
            else if (rect == &rectangle8) explosionGroundLevel = 250.0f;
            else if (rect == &rectangle9) explosionGroundLevel = 250.0f;
            else if (rect == &rectangle10) explosionGroundLevel = 280.0f;
            else if (rect == &slantedEdge1) {
                float explosionX = position.x;
                float edgeX = slantedEdge1.getPosition().x;
                float relativeX = explosionX - edgeX;
                float edgeHeight = slantedEdge1.getPosition().y;
                float slope = tan(165 * 3.1415926535 / 180);
                explosionGroundLevel = edgeHeight - (relativeX * slope);
            }
            else if (rect == &rectangle11) explosionGroundLevel = 310.0f;
            else if (rect == &rectangle12) explosionGroundLevel = 280.0f;
            else if (rect == &rectangle13) explosionGroundLevel = 310.0f;
            else if (rect == &rectangle14) explosionGroundLevel = 360.0f;
            break; // Stop checking once a collision is found
        }
    }

    float explosionBottom = position.y + (explosion.frameHeight * explosion.sprite.getScale().y) / 2.0f;
    if (explosionGroundLevel < 1000.0f && abs(explosionBottom - explosionGroundLevel) < 10.0f) {
        float adjustedY = explosionGroundLevel - (explosion.frameHeight * explosion.sprite.getScale().y) / 2.0f;
        explosion.sprite.setPosition(position.x, adjustedY);
        explosion.hitbox.setPosition(position.x, adjustedY);
    }
    else {
        // Keep original position
        explosion.sprite.setPosition(position);
        explosion.hitbox.setPosition(position);
    }

    explosions.push_back(explosion);
}

void UpdateExplosions() {
    for (auto& explosion : explosions) {
        if (!explosion.active) continue;

        explosion.timer += deltaTime;
        explosion.lifetime -= deltaTime;

        // Update animation
        if (explosion.timer >= explosion.animationSpeed) {
            explosion.timer = 0;
            explosion.frame++;
            if (explosion.frame >= explosion.frameCount || explosion.lifetime <= 0) {
                explosion.active = false;
                continue;
            }
            else {
                explosion.sprite.setTextureRect(IntRect(explosion.frame * explosion.frameWidth, 0, explosion.frameWidth, explosion.frameHeight));
            }
        }
    }

    // Remove inactive explosions
    explosions.erase(
        remove_if(explosions.begin(), explosions.end(), [](const Explosion& e) { return !e.active; }),
        explosions.end()
    );
}

void DamageMegaMan(int damage, Vector2f enemyPosition) {
    if (RestTimer <= 0.0f) {
        damageSound.play();
        Health -= damage;
        if (Health <= 0) {
            Health = 0;
            megaManDead = true;
            megamandamaged = false;
        }
        megamandamaged = true;
        RestTimer = RestDuration;
        damageTimer = 0.0f;
        damageFrame = 0;
        megamansprite.setTexture(megamanDamaged);
        megamansprite.setTextureRect(IntRect(0, 0, 72, 92));
        Vector2f megaManPos = megamansprite.getPosition();
        float knockbackDirection = (megaManPos.x < enemyPosition.x) ? -1.0f : -1.0f;
        megamansprite.move(knockbackDirection * getStepBack, 0);
    }
}

void MegaManHealth() {
    if (RestTimer > 0.0f) {
        RestTimer -= deltaTime;
    }
    if (megaManDead)
        return;

    if (megamandamaged) {
        damageTimer += deltaTime * 4;
        if (damageTimer >= DamageAnimationSpeed) {
            damageTimer = 0.0f;
            damageFrame++;
            if (damageFrame >= 9) {
                megamandamaged = false;
                damageFrame = 0;
                if (isJumping) {
                    megamansprite.setTexture(megamanJump);
                    megamansprite.setTextureRect(IntRect(0, 0, 68, 90));
                }
                else if (shooting) {
                    megamansprite.setTexture(megamanShoot);
                    megamansprite.setTextureRect(IntRect(0, 0, 73, 79));
                }
                else {
                    megamansprite.setTexture(megamanIdle);
                    megamansprite.setTextureRect(IntRect(0, 0, 74, 78));
                }
            }
            else {
                megamansprite.setTextureRect(IntRect(damageFrame * 72, 0, 72, 92));
            }
        }
    }

    if (!finalBoss.isdead && !finalBoss.isdying && playerCollider.getGlobalBounds().intersects(finalBoss.EnemyCollider.getGlobalBounds()) && RestTimer <= 0.0f) {
        DamageMegaMan(finalBoss.Damage, finalBoss.sprite.getPosition());
    }
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (!enemies[i].isdead && !enemies[i].isdying && playerCollider.getGlobalBounds().intersects(enemies[i].EnemyCollider.getGlobalBounds())) {
            DamageMegaMan(enemies[i].Damage, enemies[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < MONSTER_COUNT; i++) {
        if (!monsters[i].isdead && !monsters[i].isdying && playerCollider.getGlobalBounds().intersects(monsters[i].EnemyCollider.getGlobalBounds())) {
            DamageMegaMan(monsters[i].Damage, monsters[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < BOSS_COUNT; i++) {
        if (!bosses[i].isdead && !bosses[i].isdying && playerCollider.getGlobalBounds().intersects(bosses[i].EnemyCollider.getGlobalBounds())) {
            DamageMegaMan(bosses[i].Damage, bosses[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < ATTACK_COUNT; i++) {
        if (!attack[i].isdead && !attack[i].isdying && playerCollider.getGlobalBounds().intersects(attack[i].EnemyCollider.getGlobalBounds())) {
            DamageMegaMan(attack[i].Damage, attack[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < fly_count; i++) {
        if (!Fly[i].isdead && !Fly[i].isdying && playerCollider.getGlobalBounds().intersects(Fly[i].EnemyCollider.getGlobalBounds())) {
            DamageMegaMan(Fly[i].Damage, Fly[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < Flying_count; i++) {
        if (!flyingBot[i].isdead && !flyingBot[i].isdying && playerCollider.getGlobalBounds().intersects(flyingBot[i].EnemyCollider.getGlobalBounds())) {
            DamageMegaMan(flyingBot[i].Damage, flyingBot[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < bulletsenemy.size(); i++) {
        if (playerCollider.getGlobalBounds().intersects(bulletsenemy[i].sprite.getGlobalBounds())) {
            DamageMegaMan(bulletsenemy[i].damage, bulletsenemy[i].sprite.getPosition());
        }
    }
    for (int i = 0; i < bossBullets.size(); i++) {
        if (playerCollider.getGlobalBounds().intersects(bossBullets[i].hitbox.getGlobalBounds())) {
            DamageMegaMan(bossBullets[i].damage, bossBullets[i].bossSprite.getPosition());
            bossBullets[i].bossActive = false;
        }
    }
    for (int i = 0; i < explosions.size(); i++) {
        if (playerCollider.getGlobalBounds().intersects(explosions[i].sprite.getGlobalBounds())) {
            DamageMegaMan(explosions[i].damage, explosions[i].sprite.getPosition());
        }
    }

    int muchDamaged = 18 - Health;
    Health_Bar.setTextureRect(IntRect(muchDamaged * 64, 0, 64, 104));

}

void Health_Up(Vector2f enemyPosition, float megamanPositionY, int indx) {
    if (healthUps[indx].gotHealthUp)
        return;

    if (playerCollider.getGlobalBounds().intersects(healthUps[indx].sprite.getGlobalBounds())) {
        healthUps[indx].gotHealthUp = true;
        Health += healthUps[indx].health;
        cout << Health << endl;
        if (Health >= 18) {
            Health = 18;
        }
        cout << Health << endl;
    }

    //Animation in case not got the healthup
    if (!healthUps[indx].gotHealthUp) {
        healthUps[indx].healthUpTimer += deltaTime * 5;
        if (healthUps[indx].healthUpTimer >= healthUps[indx].healthUpAnimationSpeed) {
            healthUps[indx].healthUpTimer = 0;
            healthUps[indx].sprite.setTextureRect(IntRect(healthUps[indx].frame * 18, 0, 18, 14));
            healthUps[indx].frame++;
            healthUps[indx].frame = healthUps[indx].frame % 3;
            if (megamanPositionY <= healthUps[indx].sprite.getPosition().y - 3)
            {
                healthUps[indx].sprite.move(0.0f, 0.0f);
            }
            else
            {
                healthUps[indx].sprite.move(0.0f, 15.0f);
            }
        }
    }
}

void reset() {
    // Reset Player (Mega Man)
    megamansprite.setPosition(400.0f, 0.0f);
    Health = 18;
    megaManDead = false;
    megamandamaged = false;
    isJumping = false;
    isfalling = true;
    isFallingFast = false;
    velocityY = 0.0f;
    groundlevel = 290.0f;
    shooting = false;
    shootfinished = false;
    falldone = false;
    finalBoss.isActive = false;
    facingDirection = 1;
    jumpanimationtimer = 0;
    shootrunanimationtimer = 0.0f;
    shootanimationtimer = 0;
    runanimationtimer = 0;
    jumpshootanimationtimer = 0;
    readyanimationtimer = 0;
    falltimer = 0.0f;
    readyindx = 0;
    Idleindx = 0;
    Fallindx = 0;
    Runindx = 0;
    Jumpindx = 0;
    Shootindx = 0;
    ShootRunindx = 0;
    JumpShootindx = 0;
    ismoving = false;
    damageTimer = 0.0f;
    damageFrame = 0;
    RestTimer = 0.0f;
    megamansprite.setTexture(megamanFall);
    megamansprite.setTextureRect(IntRect(0, 0, 71, 92));
    megamansprite.setScale(1, 1);
    megamansprite.setOrigin(67 / 2, 77 / 2);

    // Reset Ready Sprite
    showready = true;
    readyclock.restart();
    readysprite.setTexture(readytexture);
    readysprite.setTextureRect(IntRect(0, 0, 76, 63));
    readysprite.setScale(1.3f, 1.3f);
    readysprite.setOrigin(76 / 2.0f, 63 / 2.0f);
    readysprite.setPosition(view.getCenter().x, view.getCenter().y);

    // Reset Health Bar
    Health_Bar.setTexture(healthBar);
    Health_Bar.setTextureRect(IntRect(0, 0, 64, 104));
    Health_Bar.setPosition(Vector2f(-50.0f, 70.0f));
    Health_Bar.setScale(4.0f, 3.0f);

    // Reset Background and Map Sprites
    backgroundSprite.setPosition(0, -40);
    mapSprite.setPosition(-10, 184);

    // Reset Car and Track Sprites
    carSprite.setPosition(600.0f, 278.0f);
    carSprite2.setPosition(800.0f, 280.0f);
    trackSprite.setPosition(950.0f, 280.0f);

    // Reset Tall Not Broken Sprite
    tall_notbroken.setTexture(tall_notbokenTex);
    tall_notbroken.setPosition(2520, 288);
    tall_notbroken.setScale(1.0f, 1.0f);
    tall_notbroken2.setPosition(3160.51, 321.508);
    tall_notbroken2.setScale(1.0f, 1.0f);
    isTallNotBrokenVisible = true;
    isTall4visible = true;
    // Reset Bullets, Bombs, and Explosions
    bullets.clear();
    bulletsenemy.clear();
    bossBullets.clear();
    bombs.clear();
    explosions.clear();

    // Reset Enemies
    float enemiesY[ENEMY_COUNT] = { 230, 215, 213, 217, 248 };
    for (int i = 0; i < ENEMY_COUNT; i++) {
        enemies[i].sprite.setTexture(enemiesTex);
        enemies[i].sprite.setTextureRect(IntRect(0, 0, 106, 114));
        enemies[i].sprite.setScale(0.9f, 0.9f);
        enemies[i].sprite.setPosition(700 + i * 700, enemiesY[i]);
        enemies[i].frame = 0;
        enemies[i].direction = 1;
        enemies[i].Health = 14;
        enemies[i].Damage = 2;
        enemies[i].isdead = false;
        enemies[i].isdying = false;
        enemies[i].deathFrame = 0;
        enemies[i].deathTimer = 0;
        enemies[i].EnemyCollider.setSize(Vector2f(30, 60));
        enemies[i].EnemyCollider.setPosition(enemies[i].sprite.getPosition());
        enemies[i].EnemyCollider.setOrigin(enemies[i].EnemyCollider.getLocalBounds().width - 62, enemies[i].EnemyCollider.getLocalBounds().height - 85);
        enemies[i].EnemyCollider.setFillColor(Color::Black);
    }

    // Reset Monsters
    float monsterY[MONSTER_COUNT] = { 243, 237, 273 };
    for (int i = 0; i < MONSTER_COUNT; i++) {
        monsters[i].sprite.setTexture(Monster1);
        monsters[i].sprite.setTextureRect(IntRect(0, 0, 161, 100));
        monsters[i].sprite.setScale(-0.7f, 0.7f);
        monsters[i].sprite.setPosition(2500 + i * 1700, monsterY[i]);
        monsters[i].frame = 0;
        monsters[i].direction = 1;
        monsters[i].Health = 10;
        monsters[i].Damage = 2;
        monsters[i].isdead = false;
        monsters[i].isdying = false;
        monsters[i].deathFrame = 0;
        monsters[i].deathTimer = 0;
        monsters[i].EnemyCollider.setSize(Vector2f(50, 40));
        monsters[i].EnemyCollider.setPosition(monsters[i].sprite.getPosition());
        monsters[i].EnemyCollider.setOrigin(monsters[i].EnemyCollider.getLocalBounds().width + 30, monsters[i].EnemyCollider.getLocalBounds().height - 60);
        monsters[i].EnemyCollider.setFillColor(Color::Black);
    }

    // Reset Big Boss
    Vector2f bossPositions[BOSS_COUNT] = { {2620, 145}, {3300, 160} };
    for (int i = 0; i < BOSS_COUNT; i++) {
        bosses[i].sprite.setTexture(big_boss);
        bosses[i].sprite.setTextureRect(IntRect(0, 0, 181, 141));
        bosses[i].sprite.setScale(1.1f, 1.1f);
        bosses[i].sprite.setPosition(bossPositions[i]);
        bosses[i].Health = 20;
        bosses[i].Damage = 6;
        bosses[i].isdead = false;
        bosses[i].isdying = false;
        bosses[i].deathFrame = 0;
        bosses[i].deathTimer = 0;
        bosses[i].frame = 0;
        bosses[i].direction = 1;
        bosses[i].EnemyCollider.setSize(Vector2f(100, 90));
        bosses[i].EnemyCollider.setPosition(bosses[i].sprite.getPosition());
        bosses[i].EnemyCollider.setOrigin(bosses[i].EnemyCollider.getLocalBounds().width - 160, bosses[i].EnemyCollider.getLocalBounds().height - 130);
        bosses[i].EnemyCollider.setFillColor(Color::Red);
    }

    // Reset Attack Enemies
    float attackY[ATTACK_COUNT] = { 234, 250, 295, 225 };
    for (int i = 0; i < ATTACK_COUNT; i++) {
        attack[i].sprite.setTexture(attacks);
        attack[i].sprite.setTextureRect(IntRect(0, 0, 78, 82));
        attack[i].sprite.setPosition(1000 + i * 1240, attackY[i]);
        attack[i].sprite.setScale(0.8f, 0.8f);
        attack[i].frame = 0;
        attack[i].direction = 1;
        attack[i].Health = 6;
        attack[i].Damage = 2;
        attack[i].isdead = false;
        attack[i].isdying = false;
        attack[i].deathFrame = 0;
        attack[i].deathTimer = 0;
        attack[i].EnemyCollider.setSize(Vector2f(20, 20));
        attack[i].EnemyCollider.setPosition(attack[i].sprite.getPosition());
        attack[i].EnemyCollider.setOrigin(attack[i].EnemyCollider.getLocalBounds().width - 42, attack[i].EnemyCollider.getLocalBounds().height - 45);
        attack[i].EnemyCollider.setFillColor(Color::Blue);
    }

    // Reset Fly Enemies
    float flyY[fly_count] = { 200, 200, 200, 200, 200 };
    for (int i = 0; i < fly_count; i++) {
        Fly[i].sprite.setTexture(FLY);
        Fly[i].sprite.setTextureRect(IntRect(0, 0, 80, 62));
        Fly[i].sprite.setScale(1.2f, 1.2f);
        Fly[i].sprite.setPosition(2300 + i * 700, flyY[i]);
        Fly[i].frame = 0;
        Fly[i].direction = 1;
        Fly[i].Health = 6;
        Fly[i].Damage = 4;
        Fly[i].isdead = false;
        Fly[i].isdying = false;
        Fly[i].deathFrame = 0;
        Fly[i].deathTimer = 0;
        Fly[i].EnemyCollider.setSize(Vector2f(23, 50));
        Fly[i].EnemyCollider.setPosition(Fly[i].sprite.getPosition());
        Fly[i].EnemyCollider.setOrigin(Fly[i].EnemyCollider.getLocalBounds().width - 70, Fly[i].EnemyCollider.getLocalBounds().height - 70);
        Fly[i].EnemyCollider.setFillColor(Color::Blue);
    }

    // Reset Final Boss
    finalBoss.sprite.setTexture(finalBossIdleTex);
    finalBoss.sprite.setTextureRect(IntRect(0, 0, 97, 119));
    finalBoss.sprite.setScale(1.1f, 1.1f);
    finalBoss.sprite.setPosition(6580, 340);
    finalBoss.frame = 0;
    finalBoss.direction = 1;
    finalBoss.timer = 0.0f;
    finalBoss.isIdle = true;
    finalBoss.isSliding = false;
    finalBoss.isWalking = false;
    finalBoss.isAttacking = false;
    finalBoss.speed = 2.0f;
    finalBoss.Health = 40;
    finalBoss.Damage = 2;
    finalBoss.isdead = false;
    finalBoss.isdying = false;
    finalBoss.deathFrame = 0;
    finalBoss.deathTimer = 0.0f;
    finalBoss.EnemyCollider.setSize(Vector2f(97, 119));
    finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
    finalBoss.EnemyCollider.setOrigin(finalBoss.EnemyCollider.getLocalBounds().width - 160, finalBoss.EnemyCollider.getLocalBounds().height - 130);
    finalBoss.EnemyCollider.setFillColor(Color::Red);
    finalBoss.sprite.setOrigin(97 / 2, 119 / 2);

    // Reset Camera View
    view.setCenter(400.0f, 300.0f);

    // Reset Boss Bullet Firing State
    isFired = false;
}

bool update(RenderWindow& window, float dt, GameState& gameState) {
    deltaTime = dt;

    if (megaManDead) {
        gameState = GAME_OVER;
        return false;
    }

    Vector2f playerCenter = megamansprite.getPosition();
    Vector2f newViewCenter = view.getCenter();
    newViewCenter.x = playerCenter.x;
    float halfCamW = view.getSize().x / 2.0f;
    float maxCamX = mapTexture.getSize().x - halfCamW;
    float minCamX = halfCamW;
    newViewCenter.x = std::max(minCamX, std::min(newViewCenter.x, maxCamX));
    view.setCenter(newViewCenter);

    float mapWidth = static_cast<float>(mapTexture.getSize().x);
    float bgWidth = static_cast<float>(backgroundTexture.getSize().x) * backgroundSprite.getScale().x;
    float bgMoveFactor = (bgWidth - window.getSize().x) / (mapWidth - window.getSize().x);
    float bgX = (view.getCenter().x - window.getSize().x / 12.0f) * bgMoveFactor;
    backgroundSprite.setPosition(-bgX, backgroundSprite.getPosition().y);

    float carSpeed = 100.0f, trackSpeed = 120.0f;
    float carEndX = -100.0f, trackEndX = -100.0f;
    carSprite.move(-carSpeed * deltaTime, 0.0f);
    if (carSprite.getPosition().x < carEndX) carSprite.setPosition(600.0f, 278.0f);
    carSprite2.move(-carSpeed * deltaTime, 0.0f);
    if (carSprite2.getPosition().x < carEndX) carSprite2.setPosition(800.0f, 280.0f);
    trackSprite.move(-trackSpeed * deltaTime, 0.0f);
    if (trackSprite.getPosition().x < trackEndX) trackSprite.setPosition(950.0f, 280.0f);

    Update_Enemies();
    UpdateBulletsenemy();
    UpdateBombs();
    UpdateExplosions();
    BossUpdateBullets();
    PlayerMovement();

    return true;
}