#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "../Header/Util.h"

// ============================================================================
// GAME STATE
// ============================================================================
enum class GameState {
    MENU,
    COOKING,
    ASSEMBLING,
    FINISHED
};

enum class IngredientType {
    BOTTOM_BUN,
    PATTY,
    KETCHUP,
    MUSTARD,
    PICKLES,
    ONION,
    LETTUCE,
    CHEESE,
    TOMATO,
    TOP_BUN
};

struct Ingredient {
    IngredientType type;
    float x, y;
    unsigned int texture;
    bool placed;
    float width, height;
    float alpha;
};

struct Puddle {
    float x, y;
    unsigned int texture;
    bool active;
    float velocityY;
};

// Game state variables
GameState currentState = GameState::MENU;
float pattyX = 0.0f;
float pattyY = 0.5f;
float cookProgress = 0.0f;
int currentIngredientIndex = 0;
Ingredient ingredients[10];
float plateY = -0.45f;
Puddle ketchupPuddles[50];
Puddle mustardPuddles[50];
int ketchupPuddleCount = 0;
int mustardPuddleCount = 0;

float transitionTimer = 0.0f;
bool isTransitioning = false;

// Input state
bool wPressed = false;
bool aPressed = false;
bool sPressed = false;
bool dPressed = false;
bool spacePressed = false;

// ============================================================================
// TEXTURES
// ============================================================================
unsigned int buttonTexture = 0;
unsigned int button2Texture = 0;
unsigned int studentInfoTexture = 0;
unsigned int stoveTexture = 0;
unsigned int tableTexture = 0;
unsigned int plateTexture = 0;
unsigned int pattyRawTexture = 0;
unsigned int pattyCookedTexture = 0;
unsigned int bottomBunTexture = 0;
unsigned int topBunTexture = 0;
unsigned int cheeseTexture = 0;
unsigned int lettuceTexture = 0;
unsigned int tomatoTexture = 0;
unsigned int picklesTexture = 0;
unsigned int onionTexture = 0;
unsigned int ketchupBottleTexture = 0;
unsigned int mustardBottleTexture = 0;
unsigned int ketchupStainTexture = 0;
unsigned int mustardStainTexture = 0;

// ============================================================================
// FUNCTIONS
// ============================================================================
void loadAllTextures() {
    std::cout << "Loading textures..." << std::endl;

    buttonTexture = loadImageToTexture("Resources/button.png");
    std::cout << "  Button: " << buttonTexture << std::endl;

    button2Texture = loadImageToTexture("Resources/button2.png");
    std::cout << "  Button: " << button2Texture << std::endl;

    studentInfoTexture = loadImageToTexture("Resources/info.png");
    std::cout << "  Student info: " << studentInfoTexture << std::endl;

    stoveTexture = loadImageToTexture("Resources/stove.png");
    std::cout << "  Stove: " << stoveTexture << std::endl;

    tableTexture = loadImageToTexture("Resources/table.png");
    std::cout << "  Table: " << tableTexture << std::endl;

    plateTexture = loadImageToTexture("Resources/plate.png");
    std::cout << "  Plate: " << plateTexture << std::endl;

    pattyRawTexture = loadImageToTexture("Resources/patty_raw.png");
    std::cout << "  Patty raw: " << pattyRawTexture << std::endl;

    pattyCookedTexture = loadImageToTexture("Resources/patty_cooked.png");
    std::cout << "  Patty cooked: " << pattyCookedTexture << std::endl;

    bottomBunTexture = loadImageToTexture("Resources/bottom_bun.png");
    std::cout << "  Bottom bun: " << bottomBunTexture << std::endl;

    topBunTexture = loadImageToTexture("Resources/top_bun.png");
    std::cout << "  Top bun: " << topBunTexture << std::endl;

    cheeseTexture = loadImageToTexture("Resources/cheese.png");
    std::cout << "  Cheese: " << cheeseTexture << std::endl;

    lettuceTexture = loadImageToTexture("Resources/lettuce.png");
    std::cout << "  Lettuce: " << lettuceTexture << std::endl;

    tomatoTexture = loadImageToTexture("Resources/tomato.png");
    std::cout << "  Tomato: " << tomatoTexture << std::endl;

    picklesTexture = loadImageToTexture("Resources/pickles.png");
    std::cout << "  Pickles: " << picklesTexture << std::endl;

    onionTexture = loadImageToTexture("Resources/onion.png");
    std::cout << "  Onion: " << onionTexture << std::endl;

    ketchupBottleTexture = loadImageToTexture("Resources/ketchup_bottle.png");
    std::cout << "  Ketchup bottle: " << ketchupBottleTexture << std::endl;

    mustardBottleTexture = loadImageToTexture("Resources/mustard_bottle.png");
    std::cout << "  Mustard bottle: " << mustardBottleTexture << std::endl;

    ketchupStainTexture = loadImageToTexture("Resources/ketchup_stain.png");
    std::cout << "  Ketchup stain: " << ketchupStainTexture << std::endl;

    mustardStainTexture = loadImageToTexture("Resources/mustard_stain.png");
    std::cout << "  Mustard stain: " << mustardStainTexture << std::endl;

    std::cout << "All textures loaded!" << std::endl;
}

void initIngredients() {
    ingredients[0] = { IngredientType::BOTTOM_BUN, 0.0f, 0.6f, bottomBunTexture, false, 0.3f, 0.15f, 0.0f };
    ingredients[1] = { IngredientType::PATTY, 0.0f, 0.6f, pattyCookedTexture, false, 0.25f, 0.15f, 0.0f };
    ingredients[2] = { IngredientType::KETCHUP, 0.0f, 0.6f, ketchupBottleTexture, false, 0.12f, 0.25f, 0.0f };
    ingredients[3] = { IngredientType::MUSTARD, 0.0f, 0.6f, mustardBottleTexture, false, 0.12f, 0.25f, 0.0f };
    ingredients[4] = { IngredientType::PICKLES, 0.0f, 0.6f, picklesTexture, false, 0.25f, 0.1f, 0.0f };
    ingredients[5] = { IngredientType::ONION, 0.0f, 0.6f, onionTexture, false, 0.25f, 0.12f, 0.0f };
    ingredients[6] = { IngredientType::LETTUCE, 0.0f, 0.6f, lettuceTexture, false, 0.28f, 0.15f, 0.0f };
    ingredients[7] = { IngredientType::CHEESE, 0.0f, 0.6f, cheeseTexture, false, 0.28f, 0.08f, 0.0f };
    ingredients[8] = { IngredientType::TOMATO, 0.0f, 0.6f, tomatoTexture, false, 0.3f, 0.12f, 0.0f };
    ingredients[9] = { IngredientType::TOP_BUN, 0.0f, 0.6f, topBunTexture, false, 0.3f, 0.15f, 0.0f };
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_W) wPressed = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_A) aPressed = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_S) sPressed = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_D) dPressed = (action != GLFW_RELEASE);
    if (key == GLFW_KEY_SPACE) spacePressed = (action == GLFW_PRESS);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (currentState == GameState::MENU) {
            currentState = GameState::COOKING;
            pattyX = 0.0f;
            pattyY = 0.5f;
            cookProgress = 0.0f;
        }
    }
}

void updateGame(float deltaTime) {
    float moveSpeed = 0.8f * deltaTime;

    if (currentState == GameState::COOKING) {
        if (wPressed) pattyY += moveSpeed;
        if (sPressed) pattyY -= moveSpeed;
        if (aPressed) pattyX -= moveSpeed;
        if (dPressed) pattyX += moveSpeed;

        pattyX = fmax(-0.9f, fmin(0.9f, pattyX));
        pattyY = fmax(-0.9f, fmin(0.9f, pattyY));

        if (pattyY < -0.5f) {
            cookProgress += deltaTime * 0.3f;
            if (cookProgress >= 1.0f) {
                cookProgress = 1.0f;
                currentState = GameState::ASSEMBLING;
                initIngredients();
                currentIngredientIndex = 0;
                isTransitioning = true;
                transitionTimer = 0.0f;
            }
        }
    }
    else if (currentState == GameState::ASSEMBLING) {
        // Tranzicija sa fade-in efektom
        if (isTransitioning) {
            transitionTimer += deltaTime * 0.8f;

            if (currentIngredientIndex < 10) {
                ingredients[currentIngredientIndex].alpha = fmin(1.0f, transitionTimer);
            }

            if (transitionTimer >= 1.0f) {
                isTransitioning = false;
                transitionTimer = 0.0f;
                if (currentIngredientIndex < 10) {
                    ingredients[currentIngredientIndex].alpha = 1.0f;
                }
            }
        }

        // Gravitacija za puddle
        float tableLeftEdge = -0.9f;
        float tableRightEdge = 0.9f;
        float tableTopSurface = -0.40f;
        float groundLevel = -0.95f;

        for (int i = 0; i < ketchupPuddleCount; i++) {
            if (ketchupPuddles[i].active) {
                ketchupPuddles[i].velocityY -= 1.5f * deltaTime;
                ketchupPuddles[i].y += ketchupPuddles[i].velocityY * deltaTime;

                if (ketchupPuddles[i].x >= tableLeftEdge && ketchupPuddles[i].x <= tableRightEdge) {
                    if (ketchupPuddles[i].y <= tableTopSurface) {
                        ketchupPuddles[i].y = tableTopSurface;
                        ketchupPuddles[i].velocityY = 0.0f;
                    }
                }
                else {
                    if (ketchupPuddles[i].y <= groundLevel) {
                        ketchupPuddles[i].y = groundLevel;
                        ketchupPuddles[i].velocityY = 0.0f;
                    }
                }
            }
        }

        for (int i = 0; i < mustardPuddleCount; i++) {
            if (mustardPuddles[i].active) {
                mustardPuddles[i].velocityY -= 1.5f * deltaTime;
                mustardPuddles[i].y += mustardPuddles[i].velocityY * deltaTime;

                if (mustardPuddles[i].x >= tableLeftEdge && mustardPuddles[i].x <= tableRightEdge) {
                    if (mustardPuddles[i].y <= tableTopSurface) {
                        mustardPuddles[i].y = tableTopSurface;
                        mustardPuddles[i].velocityY = 0.0f;
                    }
                }
                else {
                    if (mustardPuddles[i].y <= groundLevel) {
                        mustardPuddles[i].y = groundLevel;
                        mustardPuddles[i].velocityY = 0.0f;
                    }
                }
            }
        }

        if (currentIngredientIndex < 10 && !isTransitioning) {
            Ingredient& ing = ingredients[currentIngredientIndex];

            if (!ing.placed) {
                if (wPressed) ing.y += moveSpeed;
                if (sPressed) ing.y -= moveSpeed;

                // Ograničeno kretanje za kečap/senf bocice
                if (ing.type == IngredientType::KETCHUP || ing.type == IngredientType::MUSTARD) {
                    if (aPressed) ing.x -= moveSpeed;
                    if (dPressed) ing.x += moveSpeed;

                    ing.x = fmax(-0.5f, fmin(0.5f, ing.x));
                    ing.y = fmax(-0.9f, fmin(0.9f, ing.y));
                }
                else {
                    if (aPressed) ing.x -= moveSpeed;
                    if (dPressed) ing.x += moveSpeed;

                    ing.x = fmax(-0.9f, fmin(0.9f, ing.x));
                    ing.y = fmax(-0.9f, fmin(0.9f, ing.y));
                }

                if ((ing.type == IngredientType::KETCHUP || ing.type == IngredientType::MUSTARD) && spacePressed) {
                    if (ing.y < plateY + 0.5f && ing.y > plateY - 0.2f &&
                        ing.x > -0.35f && ing.x < 0.35f) {
                        ing.placed = true;
                        ing.x = 0.0f;

                        // Promeni teksturu bocice u baricu
                        if (ing.type == IngredientType::KETCHUP) {
                            ing.texture = ketchupStainTexture;
                            ing.width = 0.27f;
                            ing.height = 0.08f;
                        }
                        else {
                            ing.texture = mustardStainTexture;
                            ing.width = 0.27f;
                            ing.height = 0.08f;
                        }

                        float lastY = plateY;
                        for (int j = currentIngredientIndex - 1; j >= 0; j--) {
                            if (ingredients[j].placed) {
                                lastY = ingredients[j].y;
                                break;
                            }
                        }
                        ing.y = lastY + 0.015f;

                        currentIngredientIndex++;
                        isTransitioning = true;
                        transitionTimer = 0.0f;
                    }
                    else {
                        if (ing.type == IngredientType::KETCHUP && ketchupPuddleCount < 50) {
                            ketchupPuddles[ketchupPuddleCount] = { ing.x, ing.y - 0.15f, ketchupStainTexture, true, 0.0f };
                            ketchupPuddleCount++;
                        }
                        else if (ing.type == IngredientType::MUSTARD && mustardPuddleCount < 50) {
                            mustardPuddles[mustardPuddleCount] = { ing.x, ing.y - 0.15f, mustardStainTexture, true, 0.0f };
                            mustardPuddleCount++;
                        }
                    }
                    spacePressed = false;
                }
                else if (ing.type != IngredientType::KETCHUP && ing.type != IngredientType::MUSTARD) {
                    if (ing.y < plateY + 0.3f && ing.x > -0.2f && ing.x < 0.2f) {
                        ing.placed = true;

                        if (currentIngredientIndex == 0) {
                            ing.x = -0.01f;
                            ing.y = plateY;
                        }
                        else if (currentIngredientIndex == 1) {
                            ing.x = 0.0f;
                            ing.y = ingredients[0].y + 0.015f;
                        }
                        else {
                            ing.x = 0.0f;
                            float lastY = plateY;
                            for (int j = currentIngredientIndex - 1; j >= 0; j--) {
                                if (ingredients[j].placed &&
                                    ingredients[j].type != IngredientType::KETCHUP &&
                                    ingredients[j].type != IngredientType::MUSTARD) {
                                    lastY = ingredients[j].y;
                                    break;
                                }
                            }
                            ing.y = lastY + 0.015f;
                        }

                        currentIngredientIndex++;
                        isTransitioning = true;
                        transitionTimer = 0.0f;

                        if (currentIngredientIndex >= 10) {
                            currentState = GameState::FINISHED;
                        }
                    }
                }
            }
        }
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTexture(studentInfoTexture, -0.7, 0.9, 2.0, 2.0, 0.5);

    if (currentState == GameState::MENU) {
        if (buttonTexture != 0) {
            drawTexture(buttonTexture, 0.0f, 0.0f, 1.5f, 0.4f);
        }
        else {
            drawRect(0.0f, 0.0f, 0.8f, 0.4f, 0.3f, 0.7f, 0.3f, 1.0f);
        }
    }
    else if (currentState == GameState::COOKING) {
        drawTexture(stoveTexture, 0.0f, -0.65f, 1.0f, 0.5f);
        drawRect(0.0f, 0.75f, 1.6f, 0.08f, 0.3f, 0.3f, 0.3f);
        drawRect(-0.8f + cookProgress * 0.8f, 0.75f, cookProgress * 1.6f, 0.06f, 0.2f, 0.8f, 0.2f);

        float rawAlpha = 1.0f - cookProgress;
        float cookedAlpha = cookProgress;

        if (rawAlpha > 0.01f) {
            drawTexture(pattyRawTexture, pattyX, pattyY, 0.25f, 0.15f, rawAlpha);
        }
        if (cookedAlpha > 0.01f) {
            drawTexture(pattyCookedTexture, pattyX, pattyY, 0.25f, 0.15f, cookedAlpha);
        }
    }
    else if (currentState == GameState::ASSEMBLING) {
        drawTexture(tableTexture, 0.0f, -0.6f, 1.8f, 0.7f);
        drawTexture(plateTexture, 0.0f, plateY, 0.55f, 0.25f);

        for (int i = 0; i < ketchupPuddleCount; i++) {
            if (ketchupPuddles[i].active) {
                drawTexture(ketchupPuddles[i].texture, ketchupPuddles[i].x, ketchupPuddles[i].y, 0.12f, 0.08f);
            }
        }
        for (int i = 0; i < mustardPuddleCount; i++) {
            if (mustardPuddles[i].active) {
                drawTexture(mustardPuddles[i].texture, mustardPuddles[i].x, mustardPuddles[i].y, 0.12f, 0.08f);
            }
        }

        for (int i = 0; i < currentIngredientIndex; i++) {
            if (ingredients[i].placed) {
                drawTexture(ingredients[i].texture, ingredients[i].x, ingredients[i].y,
                    ingredients[i].width, ingredients[i].height);
            }
        }

        if (currentIngredientIndex < 10 && !ingredients[currentIngredientIndex].placed) {
            Ingredient& ing = ingredients[currentIngredientIndex];

            if (ing.type == IngredientType::KETCHUP || ing.type == IngredientType::MUSTARD) {
                drawTexture(ing.texture, ing.x, ing.y, ing.width, -ing.height, ing.alpha);
            }
            else {
                drawTexture(ing.texture, ing.x, ing.y, ing.width, ing.height, ing.alpha);
            }
        }
    }
    else if (currentState == GameState::FINISHED) {
        drawTexture(tableTexture, 0.0f, -0.6f, 1.8f, 0.7f);
        drawTexture(plateTexture, 0.0f, plateY, 0.55f, 0.25f);

        for (int i = 0; i < ketchupPuddleCount; i++) {
            if (ketchupPuddles[i].active) {
                drawTexture(ketchupPuddles[i].texture, ketchupPuddles[i].x, ketchupPuddles[i].y, 0.12f, 0.08f);
            }
        }
        for (int i = 0; i < mustardPuddleCount; i++) {
            if (mustardPuddles[i].active) {
                drawTexture(mustardPuddles[i].texture, mustardPuddles[i].x, mustardPuddles[i].y, 0.12f, 0.08f);
            }
        }

        for (int i = 0; i < 10; i++) {
            drawTexture(ingredients[i].texture, ingredients[i].x, ingredients[i].y,
                ingredients[i].width, ingredients[i].height);
        }
        drawTexture(button2Texture, 0.0f, 0.7f, 0.8f, 0.25f);
    }
}

// ============================================================================
// MAIN
// ============================================================================
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    std::cout << "Screen resolution: " << mode->width << "x" << mode->height << std::endl;

    int size = (mode->width < mode->height) ? mode->width : mode->height;
 
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Burger Game", monitor, NULL);
    if (window == NULL) return endProgram("Prozor nije uspeo da se kreira.");
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) return endProgram("GLEW nije uspeo da se inicijalizuje.");

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.95f, 0.9f, 0.85f, 1.0f);

    int offsetX = (mode->width - size) / 2;
    int offsetY = (mode->height - size) / 2;
    glViewport(offsetX, offsetY, size, size);

    std::cout << "Creating shader program..." << std::endl;
    unsigned int shaderProgram = createShader("Shaders/basic.vert", "Shaders/basic.frag");
    if (shaderProgram == 0) {
        return endProgram("Shader program nije kreiran!");
    }
    std::cout << "Shader program created: " << shaderProgram << std::endl;

    setShaderProgram(shaderProgram);
    createQuad();

    loadAllTextures();


    std::cout << "Loading cursor..." << std::endl;
    GLFWcursor* cursor = loadImageToCursor("Resources/spatula.png");
    if (cursor != nullptr) {
        glfwSetCursor(window, cursor);
        std::cout << "Cursor loaded!" << std::endl;
    }

    std::cout << "\n=== Game started ===\n" << std::endl;

    float lastTime = (float)glfwGetTime();
    const float targetFrameTime = 1.0f / 75.0f; // 75 FPS

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;

        // Ako je frame prebrz, čekaj
        if (deltaTime < targetFrameTime) {
            continue; // Preskoči ovaj frame
        }

        lastTime = currentTime;

        updateGame(deltaTime);
        renderScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}