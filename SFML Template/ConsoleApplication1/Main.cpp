#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <iomanip>
using namespace std;
using namespace sf;

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



//boss
Texture finalBossIdleTex;
Texture finalBossSlideTex;
Texture finalBossWalkTex;
Texture finalBossAttackTex;
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
    bool isdead;
    bool isdying;
    int deathFrame;
    float deathTimer;
    const float deathAnimationSpeed = 0.1f;
    RectangleShape EnemyCollider;
    FinalBoss() : frame(0), direction(1), timer(0), isIdle(true), isSliding(false), isWalking(false), isAttacking(false), speed(2.0f), Health(50), Damage(8), isdead(false), isdying(false), deathFrame(0), deathTimer(0) {}
};
FinalBoss finalBoss; // كائن واحد للـ FinalBoss

// map collisions
RectangleShape playerCollider(Vector2f(29, 33));
RectangleShape rectangle0(Vector2f(745, 48));
RectangleShape rectangle1(Vector2f(482.48, 45.417));
RectangleShape rectangle2(Vector2f(991, 47));
RectangleShape rectangle3(Vector2f(510, 47));
RectangleShape rectangle4(Vector2f(765, 47));
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

// Textures
Texture readytexture;
Texture megamanIdle;
Texture megamanRun;
Texture megamanJump;
Texture megamanShoot;
Texture megamanJumpShoot;
Texture megamanShootRun;
Texture megamanFall;
Texture bulletenemyTexture; // Bullet texture
Texture megamanDamaged;
Texture BossBulletTexture;


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

//Bullet
struct Bullet {
    Sprite sprite;
    Vector2f velocity;
    int damage = 2;
    void upDate(float deltaTime) {
        sprite.move(velocity * deltaTime);
    }
};

Bullet b;
vector<Bullet> bullets;
SoundBuffer shootBuffer;
Sound shootSound;
SoundBuffer fadeinBuffer;
Sound fadeinSound;
Texture bulletTex;
int facingDirection = 1;
bool RightWasPressed = false;


// Game State Variables
bool ismoving = false;
bool isJumping = false;
bool isfalling = true;
bool isFallingFast = false; // New variable for fast fall
float fastFallVelocity = 0.0f; // New variable for fast fall velocity
const float fastFallGravity = 6.5f; // New variable for fast fall gravity
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


struct BulletEnemy {
    Sprite sprite;
    float velocityX;
    bool active;
    int damage = 2;
};

//Enemy1 Bullet Management
vector<BulletEnemy> bulletsenemy;
const float bulletenemySpeed = -300.0f; // Move left
const int bulletenemyFrameWidth = 42; // Adjust based on your bullet spritesheet
const int bulletenemyFrameHeight = 38; // Adjust based on your bullet spritesheet
const int bulletenemyFrameCount = 1; // Single frame


//Boss Bullet Struct
struct bossBullet {
    Sprite bossSprite;
    float bossVelocityX = 10.f * std::cos(angle * 3.14159f / 180.f);
    float bossVelocityY = -10.f * std::sin(angle * 3.14159f / 180.f);
    bool bossActive;
    int damage = 2;
};
//Boss Bullet Management
vector<bossBullet> bossBullets;
const float bossBulletSpeed = -600.0f; // Move left
const int bossBulletFrameWidth = 64; // Adjust based on your bullet spritesheet
const int bossBulletFrameHeight = 63; // Adjust based on your bullet spritesheet
const int bossBulletFrameCount = 1;

//Bomb Struct
struct Bomb {
    Sprite sprite;
    float velocityY; // Vertical movement speed
    bool active;
    RectangleShape hitbox;
};

vector<Bomb> bombs;
Texture bombTexture;
const float bombSpeed = 200.0f; // Speed of bomb falling downward
const int bombFrameWidth = 55; // Bomb sprite width
const int bombFrameHeight = 56; // Bomb sprite height
const float proximityDistance = 40.0f;

//Explosion Struct
struct Explosion {
    Sprite sprite;
    int frame;
    int damage = 2;
    float timer;
    bool active;
    float animationSpeed = 0.1f; // Time per frame (adjust as needed)
    int frameCount = 7; // Number of frames in the sprite sheet
    int frameWidth = 74; // Width of each frame
    int frameHeight = 72; // Height of each frame
    float lifetime = 2.0f;
    Explosion() : frame(0), timer(0), active(false) {}
};
vector<Explosion> explosions;
Texture explosionTexture;

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
};

const int ENEMY_COUNT = 5;
const int MONSTER_COUNT = 3;
const int BOSS_COUNT = 1;
const int ATTACK_COUNT = 4;
const int fly_count = 5;

Enemy enemies[ENEMY_COUNT];
Enemy monsters[MONSTER_COUNT];
Enemy boss;
Enemy attack[ATTACK_COUNT];
Enemy Fly[fly_count];

Texture enemiesTex;
Texture Monster1;
Texture big_boss;
Texture attacks;
Texture FLY;

Sprite tall_notbroken;
Texture tall_notbokenTex;
Sprite tall_broken;
Texture tall_brokenTex;

Texture bossDeathTex;
Sprite bossDeath;
bool isBossDeathStopped = false;
const float bossDeathSpeed = 100.0f;
const float bossDeathTargetY = 380.167f;

// Prototypes
void Start_Enemies();
void Update_Enemies();
void PlayerMovement();
void Update();
void Start();
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
void SpawnExplosion(Vector2f position);
void ShootBomb(Vector2f position);
void UpdateExplosions();



int main()
{
    window.setFramerateLimit(30);
    view.zoom(0.37f);

    // Load Map
    Texture mapTexture;
    if (!mapTexture.loadFromFile("C:/SFML Template/Mega Man X material/SNES_-_Mega_Man_X_-_Intro_Stageee.png")) {
        cout << "failed to load map" << endl;
        return -1;
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setPosition(-10, 184);

    // Load Background
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
        ((float)mapSize.x / (bgSize.x + 1100)) * scaleFactor,
        ((float)mapSize.y / (bgSize.y - 60)) * scaleFactor
    );
    backgroundSprite.move(0, -40);

    // Load Cars
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

    // Load Track
    Texture trackTexture;
    if (!trackTexture.loadFromFile("C:/SFML Template/Mega Man X material/track.png")) {
        cout << "failed to load track image" << endl;
        return -1;
    }
    trackSprite.setTexture(trackTexture);

    // Setup Cars and Track
    float carSpeed = 100.f;
    float trackSpeed = 120.f;
    float carStartX = 600.f;
    float carEndX = -100.f;
    float trackStartX = 700.f;
    float trackEndX = -100.f;
    carSprite.setPosition(carStartX, 278);
    carSprite2.setPosition(carStartX + 200, 280);
    trackSprite.setPosition(trackStartX + 250, 280);

    // Initialize Game
    Start();
    Start_Enemies();
    Clock clock;

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
        }

        deltaTime = clock.restart().asSeconds();

        // Update Camera
        Vector2f playerCenter = megamansprite.getPosition();
        Vector2f camSize = view.getSize();
        Vector2f newViewCenter = view.getCenter();
        newViewCenter.x = playerCenter.x;
        float halfCamW = camSize.x / 2.f;
        float maxCamX = mapTexture.getSize().x - halfCamW;
        float minCamX = halfCamW;
        if (newViewCenter.x < minCamX) newViewCenter.x = minCamX;
        if (newViewCenter.x > maxCamX) newViewCenter.x = maxCamX;
        view.setCenter(newViewCenter);

        // Background Parallax
        float mapWidth = (float)mapTexture.getSize().x;
        float bgWidth = (float)backgroundTexture.getSize().x * backgroundSprite.getScale().x;
        float bgMoveFactor = (bgWidth - window.getSize().x) / (mapWidth - window.getSize().x);
        float bgX = (view.getCenter().x - window.getSize().x / 12.f) * bgMoveFactor;
        backgroundSprite.setPosition(-bgX, backgroundSprite.getPosition().y);

        // Car Movement
        Vector2f carPos = carSprite.getPosition();
        if (carPos.x > carEndX) {
            carPos.x -= carSpeed * deltaTime;
            if (carPos.x < carEndX)
                carPos.x = carEndX;
            carSprite.setPosition(carPos);
        }

        Vector2f carPos2 = carSprite2.getPosition();
        if (carPos2.x > carEndX) {
            carPos2.x -= carSpeed * deltaTime;
            if (carPos2.x < carEndX)
                carPos2.x = carEndX;
            carSprite2.setPosition(carPos2);
        }

        Vector2f trackPos = trackSprite.getPosition();
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
    }

    return 0;
}

void Start()
{
    groundlevel = 290.0;
    // Load Textures
    megamanFall.loadFromFile("C:/SFML Template/Mega Man X material/Fall.png");
    megamanIdle.loadFromFile("C:/SFML Template/Mega Man X material/Idle.png");
    megamanRun.loadFromFile("C:/SFML Template/Mega Man X material/Run.png");
    megamanJump.loadFromFile("C:/SFML Template/Mega Man X material/Jump.png");
    megamanShoot.loadFromFile("C:/SFML Template/Mega Man X material/Shoot.png");
    megamanShootRun.loadFromFile("C:/SFML Template/Mega Man X material/ShootRun.png");
    megamanJumpShoot.loadFromFile("C:/SFML Template/Mega Man X material/JumpShoot.png");
    readytexture.loadFromFile("C:/SFML Template/Mega Man X material/ready.png");
    if (!bulletenemyTexture.loadFromFile("C:/SFML Template/Mega Man X material/enemy bullet.png")) {
        cout << "failed to load bullet texture" << endl;
        return;
    }
    if (!BossBulletTexture.loadFromFile("C:/SFML Template/Mega Man X material/bossBullet.png")) {
        cout << "failed to load bullet texture" << endl;
        return;
    }
    if (!bombTexture.loadFromFile("C:/SFML Template/Mega Man X material/grenade.png")) {
        cout << "Failed to load bomb texture" << endl;
        return;
    }
    if (!explosionTexture.loadFromFile("C:/SFML Template/Mega Man X material/explosion.png")) {
        cout << "Failed to load explosion texture" << endl;
        return;
    }



    // Setup Ready Sprite
    readysprite.setTexture(readytexture);
    readysprite.setTextureRect(IntRect(0, 0, 76, 63));
    readysprite.setScale(1.3f, 1.3f);
    readysprite.setOrigin(76 / 2.0f, 63 / 2.0f);
    readysprite.setPosition(view.getCenter().x, view.getCenter().y);

    // collisions
    playerCollider.setOrigin(playerCollider.getGlobalBounds().width / 2, playerCollider.getGlobalBounds().height / 2 - 22.5);
    rectangle0.setPosition(44.8, 283.5);
    rectangle1.setPosition(830.4, 284.583);
    rectangle2.setPosition(1340.33, 283);
    rectangle3.setPosition(2379, 282);
    rectangle4.setPosition(2941.34, 282);
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

    // Setup Mega Man Sprite
    megamansprite.setTexture(megamanFall);
    megamansprite.setTextureRect(IntRect(0, 0, 71, 92));
    megamansprite.setScale(1, 1);
    megamansprite.setOrigin(67 / 2, 77 / 2);
    megamansprite.setPosition(400, 0);

    if (!attackDeathTex.loadFromFile("C:/SFML Template/Mega Man X material/attack die.png")) {
        cout << "Failed to load  attackDeathTex png\n";
    }

    if (!dieEffect.loadFromFile("C:/SFML Template/Mega Man X material/die effect.png")) {
        cout << "Failed to load dieEffect  png\n";
    }

    if (!shootBuffer.loadFromFile("C:/SFML Template/Mega Man X material/01 - MMX - X Regular Shot.wav")) {
        cout << "Failed to load shoot sound!\n";
    }
    shootSound.setBuffer(shootBuffer);

    if (!fadeinBuffer.loadFromFile("C:/SFML Template/Mega Man X material/17 - MMX - X Fade In.wav")) {
        cout << "Failed to load shoot sound!\n";
    }
    fadeinSound.setBuffer(fadeinBuffer);

    if (!bulletTex.loadFromFile("C:/SFML Template/Mega Man X material/Bullet.png"))
    {
        cout << "Failed to load bullet png.\n";
    }
    if (!megamanDamaged.loadFromFile("C:/SFML Template/Mega Man X material/Mega_Man_Damaged.png")) {
        cout << "Failed to load Mega_Man_Damaged  png\n";
    }
    if (!bossDeathTex.loadFromFile("C:/SFML Template/Mega Man X material/boss die.png")) {
        cout << "Failed to load bossDeathTex png\n";
    }

    if (!healthBar.loadFromFile("C:/SFML Template/Mega Man X material/health bar.png")) {
        cout << "Failed to load health bar  png\n";
    }
    if (!tall_notbokenTex.loadFromFile("E:/Adam Material/Mega Man X material/tall_notbroken.png")) {
        cout << "Failed to load tall not broken\n";
    }
    if (!tall_brokenTex.loadFromFile("E:/Adam Material/Mega Man X material/tall_broken.png")) {
        cout << "Failed to load tall broken\n";
    }
    tall_notbroken.setTexture(tall_notbokenTex);
    Health_Bar.setTexture(healthBar);
    Health_Bar.setTextureRect(IntRect(0, 0, 64, 104));
    Health_Bar.setPosition(Vector2f(-50.0f, 70.0f));
    Health_Bar.setScale(4.0f, 3.0f);
    tall_notbroken.setPosition(2520, 288);
    tall_notbroken.setScale(1.0f, 1.0f);
    // Initialize Falling State
    isfalling = true;
    Fallindx = 0;
    falltimer = 0;
    velocityY = 0;
}

void Update()
{
    // Map collisions
    playerCollider.setPosition(megamansprite.getPosition());
    bool isOnPlatform = false; // To track if the player is on any platform

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
    else if (playerCollider.getGlobalBounds().intersects(rectangle3.getGlobalBounds())) {
        groundlevel = 282.0f;
        if (!isJumping && !isfalling) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            velocityY = 0;
            isfalling = false;
        }
        isOnPlatform = true;
    }
    else if (playerCollider.getGlobalBounds().intersects(rectangle4.getGlobalBounds())) {
        groundlevel = 315.0f;
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
        groundlevel = 1000.0f; // Default ground level when not on any platform
        if (!isJumping && !isfalling) {
            isFallingFast = true; // Start fast falling if not on platform
            fastFallVelocity = 0.0f; // Reset fast fall velocity
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

    // Handle fast falling when not on any platform
    if (isFallingFast) {
        fastFallVelocity += fastFallGravity; // Apply fast fall gravity
        megamansprite.move(0, fastFallVelocity); // Move downward with fast fall velocity
        float currentY = megamansprite.getPosition().y;

        // Use the 5th frame of jump animation (index 4)
        megamansprite.setTexture(megamanJump);
        Jumpindx = 4; // 5th frame (0-based index)
        megamansprite.setTextureRect(IntRect(Jumpindx * 68, 0, 68, 90));

        // Check if the player reaches the ground
        if (currentY + fastFallVelocity >= groundlevel) {
            megamansprite.setPosition(megamansprite.getPosition().x, groundlevel);
            isFallingFast = false;
            fastFallVelocity = 0.0f;
            megamansprite.setTexture(megamanIdle);
            megamansprite.setTextureRect(IntRect(0, 0, 74, 78));
        }
        return;
    }

    // Enforce Map Boundaries
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
}


void Draw()
{
    window.clear();
    window.setView(window.getDefaultView());
    window.draw(backgroundSprite);
    window.setView(view);
    window.draw(mapSprite);
    window.draw(tall_notbroken);
    window.draw(carSprite2);

    for (auto& bullet : bullets) {
        window.draw(bullet.sprite);
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (!enemies[i].isdead) {
            window.draw(enemies[i].sprite);
            //window.draw(enemies[i].EnemyCollider);
        }
    }

    for (int i = 0; i < MONSTER_COUNT; i++) {
        if (!monsters[i].isdead) {
            window.draw(monsters[i].sprite);
            //window.draw(monsters[i].EnemyCollider);
        }
    }

    //finalboss
    if (!finalBoss.isdead) {
        window.draw(finalBoss.sprite);
        // window.draw(finalBoss.EnemyCollider); // للاختبار فقط
    }

    if (!boss.isdead && !boss.isdying) {
        window.draw(boss.sprite);
        //window.draw(boss.EnemyCollider);
    }
    if (boss.isdead || boss.isdying) {
        window.draw(bossDeath);
    }

    for (int i = 0; i < ATTACK_COUNT; i++) {
        if (!attack[i].isdead) {
            window.draw(attack[i].sprite);
            //window.draw(attack[i].EnemyCollider);
        }
    }

    for (int i = 0; i < fly_count; i++) {
        if (!Fly[i].isdead) {
            window.draw(Fly[i].sprite);
            //window.draw(Fly[i].EnemyCollider);
        }
    }


    if (showready) {
        window.draw(readysprite);
    }
    else if (!megaManDead) {
        window.draw(megamansprite);
    }
    // Draw Bullets
    for (auto& bullete : bulletsenemy) {
        if (bullete.active) {
            window.draw(bullete.sprite);
        }
    }
    // Draw Boss Bullets
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

    window.draw(carSprite);
    window.draw(trackSprite);
    window.setView(window.getDefaultView());
    window.draw(Health_Bar);

    window.display();
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

void bossShootBullet(Vector2f bossPosition)
{
    bossBullet bossBullet;
    bossBullet.bossSprite.setTexture(BossBulletTexture);
    bossBullet.bossSprite.setTextureRect(IntRect(0, 0, bossBulletFrameWidth, bossBulletFrameHeight));
    bossBullet.bossSprite.setScale(1.0f, 1.0f);
    bossBullet.bossSprite.setOrigin(bossBulletFrameWidth / 2.0f, bossBulletFrameHeight / 2.0f); // Center the bullet sprite

    // Position bullet at boss's mouth (approx. center horizontally, 20% from top vertically)
    float mouthOffsetX = 99.55f; // 181/2 * 1.1
    float mouthOffsetY = 31.02f; // 141*0.2 * 1.1
    bossBullet.bossSprite.setPosition(bossPosition.x + mouthOffsetX, bossPosition.y + 70 + mouthOffsetY);

    // Set velocities
    bossBullet.bossVelocityX = bossBulletSpeed; // Move left (e.g., -600.0f)
    bossBullet.bossVelocityY = 200.0f; // Positive for downward movement

    bossBullet.bossActive = true;
    bossBullets.push_back(bossBullet);

    if (isFired) {

        bossBullet.bossVelocityY += gravity * deltaTime;
        Vector2f position = bossBullet.bossSprite.getPosition();
        bossPosition.x += bossBullet.bossVelocityX * deltaTime * 60.f;
        bossPosition.y += bossBullet.bossVelocityY * deltaTime * 60.f;
        bossBullet.bossSprite.setPosition(position);

        float rotation = std::atan2(bossBullet.bossVelocityY, bossBullet.bossVelocityX) * 180.f / 3.14159f;
        bossBullet.bossSprite.setRotation(rotation);

        if (position.y > 550.f) {
            isFired = false;
            bossBullet.bossSprite.setPosition(100.f, 500.f); // إعادة الطلقة لنقطة البداية
            bossBullet.bossVelocityY = -10.f * std::sin(angle * 3.14159f / 180.f);
            bossBullet.bossSprite.setRotation(0);
        }
    }
}

void BossUpdateBullets()
{
    for (auto& bossBullet : bossBullets) {
        if (!bossBullet.bossActive) continue;

        // Update position with both horizontal and vertical velocities
        bossBullet.bossSprite.move(bossBullet.bossVelocityX * deltaTime, bossBullet.bossVelocityY * deltaTime);

        // Deactivate if off-screen or hits the ground
        float bulletY = bossBullet.bossSprite.getPosition().y;
        if (bossBullet.bossSprite.getPosition().x < 0 ||
            bossBullet.bossSprite.getPosition().x > 6651 ||
            bulletY >= 360.0f) { // Ground level at boss's area
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

    bool pressingRight = Keyboard::isKeyPressed(Keyboard::C);
    bool pressingD = Keyboard::isKeyPressed(Keyboard::D);
    bool pressingA = Keyboard::isKeyPressed(Keyboard::A);
    bool pressingSpace = Keyboard::isKeyPressed(Keyboard::Space);

    // Shoot + Jump
    if (pressingRight && isJumping) {
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
    else if (pressingRight && (pressingD || pressingA)) {
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
    if (pressingRight) {
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
        enemies[i].Health = 16;
        enemies[i].Damage = 2;
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
        monsters[i].EnemyCollider.setPosition(monsters[i].sprite.getPosition());                             //كل اما تزود الyبالسالب كل اما ينزل لتحت
        monsters[i].EnemyCollider.setOrigin(monsters[i].EnemyCollider.getLocalBounds().width + 30, monsters[i].EnemyCollider.getLocalBounds().height - 60);
        monsters[i].EnemyCollider.setFillColor(Color::Black);  //كل اما تقلل الاكس بالسالب كل ما تروح يمين
        monsters[i].Health = 10;
        monsters[i].Damage = 2;
    }

    big_boss.loadFromFile("C:/SFML Template/Mega Man X material/BIGBOSS.png");

    boss.sprite.setTexture(big_boss);
    boss.sprite.setTextureRect(IntRect(0, 0, 181, 141));
    boss.sprite.setScale(1.1f, 1.1f);
    boss.sprite.setPosition(2729, 200);
    boss.EnemyCollider.setSize(Vector2f(100, 90));
    boss.EnemyCollider.setPosition(boss.sprite.getPosition());
    boss.EnemyCollider.setOrigin(boss.EnemyCollider.getLocalBounds().width - 160, boss.EnemyCollider.getLocalBounds().height - 130);
    boss.EnemyCollider.setFillColor(Color::Red);
    boss.Health = 30;
    boss.Damage = 6;



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
        Fly[i].sprite.setPosition(2300 + i * 700, flyY[i]);
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
    finalBoss.sprite.setPosition(630, 265);
    finalBoss.EnemyCollider.setSize(Vector2f(100, 90));
    finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition());
    finalBoss.EnemyCollider.setOrigin(finalBoss.EnemyCollider.getLocalBounds().width - 160, finalBoss.EnemyCollider.getLocalBounds().height - 130);
    finalBoss.EnemyCollider.setFillColor(Color::Red);
    finalBoss.Health = 50;
    finalBoss.Damage = 5;
    finalBoss.sprite.setOrigin(97 / 2, 119 / 2);
}
void Update_Enemies() {
    static Clock clock;
    static float delay = 0.2f;
    static float time = 0.1f;
    static Clock clock2;
    Vector2f playerPos = megamansprite.getPosition();

    if (clock2.getElapsedTime().asSeconds() >= time) {
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
                    attack[i].sprite.move(-2.f, 0);
                    attack[i].EnemyCollider.move(-2.f, 0);
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

        if (boss.isdying || boss.isdead) {
            if (bossDeath.getPosition().y == 380.167) {
                bossDeath.move(0.0f, 0.0f);
            }
            else {
                bossDeath.move(0.0f, 15.0f);
            }
        }

        else if (!boss.isdead) {
            Vector2f bossPosition = boss.sprite.getPosition();
            float distance2 = abs(playerPos.x - bossPosition.x);
            if (distance2 <= 300.0f) {
                boss.sprite.setTextureRect(IntRect(boss.frame * 181, 0, 181, 141));
                boss.frame++;
                boss.frame = boss.frame % 6;
                boss.sprite.move(0.0f, 0);
                boss.EnemyCollider.move(0.0f, 0);
                bossShootBullet(bossPosition);

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
            }
        }
    }
    else if (!finalBoss.isdead) {
        Vector2f playerPos = megamansprite.getPosition();
        Vector2f bossPos = finalBoss.sprite.getPosition();
        float distance = playerPos.x - bossPos.x;

        // تحديد الاتجاه بناءً على موقع اللاعب
        if (distance > 0) {
            finalBoss.direction = 1; // اللاعب على اليمين
            finalBoss.sprite.setScale(1.1f, 1.1f);
        }
        else {
            finalBoss.direction = -1; // اللاعب على الشمال
            finalBoss.sprite.setScale(-1.1f, 1.1f);
        }

        // أول 5 ثواني: Idle
        if (finalBoss.isIdle) {
            finalBoss.timer += deltaTime;
            finalBoss.sprite.setTexture(finalBossIdleTex);
            finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 97, 0, 97, 116));
            finalBoss.sprite.setOrigin(97 / 2, 98/2);
            finalBoss.frame = (finalBoss.frame + 1) % 4;
            if (finalBoss.timer >= 5.0f) {
                finalBoss.isIdle = false;
                finalBoss.isSliding = true; // الانتقال إلى حالة Slide
                finalBoss.timer = 0;
                finalBoss.speed = 5.0f; // سرعة أكبر للـ Slide
            }
        }
        // حالة Slide: أول حركة
        else if (finalBoss.isSliding) {
            finalBoss.sprite.setTexture(finalBossSlideTex);
            finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 57, 0, 57, 76));
            finalBoss.frame = (finalBoss.frame + 1) % 1; 
            finalBoss.sprite.move(finalBoss.direction * finalBoss.speed, 0);
            finalBoss.EnemyCollider.move(finalBoss.direction * finalBoss.speed, 0);

            // الانتقال إلى Walk بعد الاقتراب من اللاعب (مسافة 300 مثلاً)
            distance = abs(playerPos.x - finalBoss.sprite.getPosition().x);
            if (distance <= 300.0f) {
                finalBoss.isSliding = false;
                finalBoss.isWalking = true;
                finalBoss.speed = 2.0f; // سرعة أقل للـ Walk
            }
        }
        // حالة Walk: الجري وراء اللاعب
        else if (finalBoss.isWalking) {
            finalBoss.sprite.setTexture(finalBossWalkTex);
            finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 98, 0, 98, 122));
            finalBoss.sprite.setOrigin(97 / 2, 119/2);
            finalBoss.frame = (finalBoss.frame + 1) % 9; 
            finalBoss.sprite.move(finalBoss.direction * finalBoss.speed, 0);
            finalBoss.EnemyCollider.move(finalBoss.direction * finalBoss.speed, 0);

            // الانتقال إلى Attack لما يقرب جدًا (مسافة 50 مثلاً)
            distance = abs(playerPos.x - finalBoss.sprite.getPosition().x);
            if (distance <= 50.0f) {
                finalBoss.isWalking = false;
                finalBoss.isAttacking = true;
                finalBoss.speed = 0.0f; // توقف الحركة في وضعية الهجوم
            }
        }
        // حالة Attack: قريب جدًا من اللاعب
        else if (finalBoss.isAttacking) {
            finalBoss.sprite.setTexture(finalBossAttackTex);
            finalBoss.timer += deltaTime; 
            finalBoss.sprite.setOrigin(97 / 2, 108/2);
            const float attackAnimationSpeed = 0.04f;
            if (finalBoss.timer >= attackAnimationSpeed) {
                finalBoss.timer = 0;
                finalBoss.frame = (finalBoss.frame + 1) % 3;
            }
            finalBoss.sprite.setTextureRect(IntRect(finalBoss.frame * 112, 0, 112, 118));
            float distance = playerPos.x - finalBoss.sprite.getPosition().x;
            if (distance > 0) {
                finalBoss.sprite.setScale(1.1f, 1.1f); // يمين
            }
            else {
                finalBoss.sprite.setScale(-1.1f, 1.1f); // شمال
            }
            finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition().x + (finalBoss.direction * 50), finalBoss.sprite.getPosition().y + 20);

            finalBoss.EnemyCollider.setSize(Vector2f(83, 118));
            finalBoss.EnemyCollider.setOrigin(83 / 2, 118 / 2); 
            finalBoss.EnemyCollider.setPosition(finalBoss.sprite.getPosition().x + (finalBoss.direction * 30), finalBoss.sprite.getPosition().y);
           
            if (abs(distance) > 50.0f) {
                finalBoss.isAttacking = false;
                finalBoss.isWalking = true;
                finalBoss.speed = 2.0f;
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

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::C)) && !RightWasPressed)
    {
        shootSound.play();
        Bullet b;
        b.sprite.setTexture(bulletTex);
        b.sprite.setScale(0.9f * facingDirection, 0.9f);
        int setX = 1 * facingDirection;
        if (isJumping) {
            if (facingDirection == -1) {
                b.sprite.setPosition(megamansprite.getPosition().x + setX, megamansprite.getPosition().y - 6);
            }
            else if (facingDirection == 1) {
                b.sprite.setPosition(megamansprite.getPosition().x - setX, megamansprite.getPosition().y - 6);
            }
        }
        else {
            b.sprite.setPosition(megamansprite.getPosition().x + setX, megamansprite.getPosition().y - 6);
        }
        b.velocity = Vector2f(250 * facingDirection, 0);
        bullets.push_back(b);
        RightWasPressed = true;


    }
    if (!Keyboard::isKeyPressed(Keyboard::C)) {
        RightWasPressed = false;
    }

}

void HandelingBullets() {
    for (int i = 0; i < bullets.size();) {

        bullets[i].upDate(deltaTime);

        bool bulletHit = false;

        if (bullets[i].sprite.getPosition().x < megamansprite.getPosition().x - 140 ||
            bullets[i].sprite.getPosition().x > megamansprite.getPosition().x + 140)
        {
            bullets.erase(bullets.begin() + i);
            continue;
        }



        for (int j = 0; j < ENEMY_COUNT; j++) {
            if (!enemies[j].isdead && !enemies[j].isdying && bullets[i].sprite.getGlobalBounds().intersects(enemies[j].EnemyCollider.getGlobalBounds())) {
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
            if (!monsters[j].isdead && !monsters[j].isdying && bullets[i].sprite.getGlobalBounds().intersects(monsters[j].EnemyCollider.getGlobalBounds())) {
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

        if (!boss.isdead && !boss.isdying && bullets[i].sprite.getGlobalBounds().intersects(boss.EnemyCollider.getGlobalBounds())) {
            boss.Health -= bullets[i].damage;
            if (boss.Health <= 0) {
                boss.isdying = true;
                bossDeath.setTexture(bossDeathTex);
                bossDeath.setPosition(boss.sprite.getPosition().x + 10, boss.sprite.getPosition().y);
                bossDeath.setScale(1.1f, 1.4f);

            }
            bulletHit = true;
            break;
        }

        if (!finalBoss.isdead && !finalBoss.isdying && bullets[i].sprite.getGlobalBounds().intersects(finalBoss.EnemyCollider.getGlobalBounds())) {
            finalBoss.Health -= bullets[i].damage;
            if (finalBoss.Health <= 0) {
                finalBoss.isdying = true;
                finalBoss.sprite.setTexture(dieEffect);
                finalBoss.sprite.setTextureRect(IntRect(0, 0, 74, 72));
                finalBoss.deathFrame = 0;
            }
            bulletHit = true;
            break;
        }

        for (int j = 0; j < ATTACK_COUNT; j++) {
            if (!attack[j].isdead && !attack[j].isdying && bullets[i].sprite.getGlobalBounds().intersects(attack[j].EnemyCollider.getGlobalBounds())) {
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
            if (!Fly[j].isdead && !Fly[j].isdying && bullets[i].sprite.getGlobalBounds().intersects(Fly[j].EnemyCollider.getGlobalBounds())) {
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

void UpdateBombs()
{
    Vector2f playerPos = megamansprite.getPosition();
    playerCollider.setPosition(playerPos);

    for (auto& bomb : bombs) {
        if (!bomb.active) continue;

        // Update position (move downward)
        bomb.sprite.move(0, bomb.velocityY * deltaTime);
        bomb.hitbox.setPosition(bomb.sprite.getPosition().x - 15.0f, bomb.sprite.getPosition().y - 15.0f); // Update hitbox with sprite

        // Check proximity to player
        float distance = sqrt(pow(playerPos.x - bomb.sprite.getPosition().x, 2) + pow(playerPos.y - bomb.sprite.getPosition().y, 2));
        if (distance <= proximityDistance) {
            SpawnExplosion(bomb.sprite.getPosition());
            DamageMegaMan(2, bomb.sprite.getPosition()); // Apply damage (use explosion.damage or custom value)
            bomb.active = false;
            continue;
        }

        // Check collision with ground (stop at groundlevel + 50)
        float bombBottom = bomb.sprite.getPosition().y + (bombFrameHeight * bomb.sprite.getScale().y) / 2;
        float targetLevel = groundlevel + 50.0f;
        if (bombBottom >= targetLevel) {
            bomb.sprite.setPosition(bomb.sprite.getPosition().x, targetLevel - (bombFrameHeight * bomb.sprite.getScale().y) / 2);
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
    explosion.sprite.setPosition(position);
    explosion.active = true;
    explosion.frame = 0;
    explosion.timer = 0;
    explosion.lifetime = 2.0f;
    explosions.push_back(explosion);
}


void UpdateExplosions() {
    for (auto& explosion : explosions) {
        if (!explosion.active) continue;

        explosion.timer += deltaTime;
        explosion.lifetime -= deltaTime;

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
    static bool wasDamagedByBoss = false;
    if (!finalBoss.isdead && !finalBoss.isdying && playerCollider.getGlobalBounds().intersects(finalBoss.EnemyCollider.getGlobalBounds())) {
        if (!wasDamagedByBoss && RestTimer <= 0.0f) {
            DamageMegaMan(finalBoss.Damage, finalBoss.sprite.getPosition());
            wasDamagedByBoss = true;
        }
    }
    else {
        wasDamagedByBoss = false; // إعادة تهيئة المتغير لو التصادم انتهى
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
    if (!boss.isdead && !boss.isdying && playerCollider.getGlobalBounds().intersects(boss.EnemyCollider.getGlobalBounds())) {
        DamageMegaMan(boss.Damage, boss.sprite.getPosition());
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

    for (int i = 0; i < bulletsenemy.size(); i++) {
        if (playerCollider.getGlobalBounds().intersects(bulletsenemy[i].sprite.getGlobalBounds())) {
            DamageMegaMan(bulletsenemy[i].damage, bulletsenemy[i].sprite.getPosition());
        }
    }

    for (int i = 0; i < bossBullets.size(); i++) {
        if (playerCollider.getGlobalBounds().intersects(bossBullets[i].bossSprite.getGlobalBounds())) {
            DamageMegaMan(bossBullets[i].damage, bossBullets[i].bossSprite.getPosition());
        }
    }

    for (int i = 0; i < explosions.size(); i++) {
        if (playerCollider.getGlobalBounds().intersects(explosions[i].sprite.getGlobalBounds())) {
            DamageMegaMan(explosions[i].damage, explosions[i].sprite.getPosition());
        }
    }

    if (Health == 16)
        Health_Bar.setTextureRect(IntRect(1 * 64, 0, 64, 104));
    if (Health == 14)
        Health_Bar.setTextureRect(IntRect(2 * 64, 0, 64, 104));
    if (Health == 12)
        Health_Bar.setTextureRect(IntRect(3 * 64, 0, 64, 104));
    if (Health == 10)
        Health_Bar.setTextureRect(IntRect(4 * 64, 0, 64, 104));
    if (Health == 8)
        Health_Bar.setTextureRect(IntRect(5 * 64, 0, 64, 104));
    if (Health == 6)
        Health_Bar.setTextureRect(IntRect(6 * 64, 0, 64, 104));
    if (Health == 4)
        Health_Bar.setTextureRect(IntRect(7 * 64, 0, 64, 104));
    if (Health == 2)
        Health_Bar.setTextureRect(IntRect(8 * 64, 0, 64, 104));
    if (Health == 0)
        Health_Bar.setTextureRect(IntRect(9 * 64, 0, 64, 104));
}