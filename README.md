# Space-Shooter-Game
1. The Core Architecture: Game Loop
The heart of any game engine is the Game Loop. This is a continuous cycle that keeps the game alive. It follows three fundamental steps:

Input: Detecting player actions (keyboard presses, mouse movements).

Update: Calculating the game logic (moving characters, checking physics, updating scores).

Render: Clearing the previous frame and drawing the new positions of all objects onto the screen.

2. Entity Management System
To write "Clean Code," we used Inheritance. Instead of creating separate variables for every single object, we created a Base Class called Entity.

Every object (Player, Enemy, Bullet) inherits from this class.

This allows us to manage hundreds of objects within a single std::vector, making the engine scalable and organized.

3. Handling Time: Delta Time (dt)
One of the most professional aspects we implemented was Delta Time.

The Problem: Games run at different speeds on different computers (60 FPS vs 144 FPS).

The Solution: By calculating the time passed between two frames (dt), we ensure that movement is calculated "per second" rather than "per frame." This makes the game speed consistent on every hardware.

4. Resource Management
To optimize memory, we built a Resource Manager.

Loading a texture (image) from the hard drive is a heavy task.

Our manager ensures that each image is loaded into RAM only once. Different game objects then simply point to that single memory address, saving a significant amount of system resources.

5. Collision Detection (AABB)
We used the AABB (Axis-Aligned Bounding Box) method to detect hits.

The engine checks if the rectangular borders (hitboxes) of two sprites intersect.

When a bullet’s hitbox overlaps with an enemy’s hitbox, the engine triggers a "collision event," resulting in a score increase and an explosion.

6. Particle Systems and Game Feel
To improve "Game Feel," we added a Particle System.

When an enemy is destroyed, it doesn't just vanish; it spawns multiple tiny squares (particles) that fly in random directions and slowly fade away.

This provides visual feedback and makes the combat feel much more satisfying for the player.

7. Scrolling Background and Parallax
To create the illusion of deep space, we implemented a Scrolling Background.

We use two identical images. When the first one moves off-screen, it "teleports" back to the top.

This creates a seamless, infinite loop. Moving different layers at different speeds (Parallax) adds a 3D depth effect to a 2D game.

8. Difficulty Scaling and UI
A good game must challenge the player. We added Difficulty Scaling:

As the score increases, the difficultyLevel multiplier rises, making enemies move faster and spawn more frequently.

The HUD (Heads-Up Display) translates raw data (integers and floats) into human-readable text on the screen, showing the player's current health, score, and difficulty multiplier.

9. Game States and Menu System
Finally, we structured the game using Game States.

The engine can switch between MENU, PLAYING, and GAME_OVER states.

This allows us to have a functional Main Menu with "Start" and "Exit" buttons before the actual game logic begins, giving the project a professional "finished product" feel.
