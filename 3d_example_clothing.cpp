class ShirtPart : public Part {
public:
    ShirtPart(float x, float y, float z)
        : x(x), y(y), z(z) {}

    void render() override {
        glPushMatrix();
        glTranslatef(x, y, z);
        glBindTexture(GL_TEXTURE_2D, loadTexture("shirt.png"));
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-width/2, -height/2, 0);
        glTexCoord2f(1, 0); glVertex3f(width/2, -height/2, 0);
        glTexCoord2f(1, 1); glVertex3f(width/2, height/2, 0);
        glTexCoord2f(0, 1); glVertex3f(-width/2, height/2, 0);
        glEnd();
        glPopMatrix();
    }

private:
    float width = 20.0f;
    float height = 15.0f;
};

class PantsPart : public Part {
public:
    PantsPart(float x, float y, float z)
        : x(x), y(y), z(z) {}

    void render() override {
        glPushMatrix();
        glTranslatef(x, y, z);
        glBindTexture(GL_TEXTURE_2D, loadTexture("pants.png"));
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-width/2, -height/2, 0);
        glTexCoord2f(1, 0); glVertex3f(width/2, -height/2, 0);
        glTexCoord2f(1, 1); glVertex3f(width/2, height/2, 0);
        glTexCoord2f(0, 1); glVertex3f(-width/2, height/2, 0);
        glEnd();
        glPopMatrix();
    }

private:
    float width = 30.0f;
    float height = 20.0f;
};

class JacketPart : public Part {
public:
    JacketPart(float x, float y, float z)
        : x(x), y(y), z(z) {}

    void render() override {
        glPushMatrix();
        glTranslatef(x, y, z);
        glBindTexture(GL_TEXTURE_2D, loadTexture("jacket.png"));
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-width/2, -height/2, 0);
        glTexCoord2f(1, 0); glVertex3f(width/2, -height/2, 0);
        glTexCoord2f(1, 1); glVertex3f(width/2, height/2, 0);
        glTexCoord2f(0, 1); glVertex3f(-width/2, height/2, 0);
        glEnd();
        glPopMatrix();
    }

private:
    float width = 25.0f;
    float height = 18.0f;
};
```
**Character Class**
```cpp
class Character {
public:
    std::vector<Clothing*> outfits;

    void addOutfit(Clothing* outfit) { outfits.push_back(outfit); }

    void render() {
        for (auto& outfit : outfits) {
            outfit->render();
        }
    }

    virtual ~Character() {}
};
```
**Example Usage**
```cpp
int main() {
    // Create a character
    Character character;

    // Add an outfit to the character
    Clothing* shirt = new ShirtPart(0, 0, -10.0f);
    clothing->addOutfit(shirt);

    Clothing* pants = new PantsPart(-5.0f, 0, -10.0f);
    clothing->addOutfit(pants);

    Clothing* jacket = new JacketPart(5.0f, 0, -10.0f);
    clothing->addOutfit(jacket);

    // Render the character
    character.render();

    return 0;
}
/*
This is a very basic example and there are many ways to improve it (e.g., using more advanced cloth simulation
techniques, adding more clothing parts, etc.).

Note: This code uses OpenGL for rendering, so you'll need to set up an OpenGL context and load the necessary
textures for each clothing part.

Also, this is a simplified example, in real-world applications you would likely want to use a 3D modeling
software to create the clothing models, and then import those into your game or simulation.
*/