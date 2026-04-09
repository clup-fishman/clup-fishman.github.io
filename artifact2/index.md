---
layout: default
title: Artifact Two
---

# Artifact Two: Algorithms and Data Structures

{% include back-button.html %}

## Narrative

The artifact I selected was the Coding Collisions assignment originally developed in the CS-330 Computer Graphics and Visualization class. The original assignment started with a basic example that spawned balls in one of eight fixed directions and allowed them to interact with reflective and destructible bricks. The original goal of the assignment was to focus on rendering and interaction rather than algorithm design, but it also allowed creative freedom in implementation, which led me to model it after the classic game Brick Breaker. My implementation was a basic recreation of the core functionality of that game. This simulates the game environment where balls interact with a grid of bricks (and each other) and a player-controlled paddle. Each brick has properties such as position, color, hit points, and type (reflective or destructible). For the enhancement, I focused specifically on improving the brick grid generation logic to better demonstrate my understanding of algorithms and data structures.

I selected this artifact because it provided a strong opportunity to improve an existing system using more structured algorithmic thinking. While the original project functioned correctly, the brick generation logic was fairly basic and did not fully demonstrate intentional use of data structures or controlled algorithms.

The main component that demonstrates my skills in this category is the redesigned brick grid generation system. I refactored the original approach into a multi-stage algorithm that separates layout construction, validation, and object creation. One of the key improvements was introducing a two-dimensional vector ```vector<vector<BrickLayoutType>>``` to represent the grid layout before creating the actual brick objects. This allowed me to apply rules and constraints more effectively, such as limiting consecutive wall placements and ensuring the grid remains playable. Additionally, I implemented helper functions to isolate specific pieces of logic, such as determining when to place wall bricks and ensuring the bottom row always contains at least one breakable brick. This improved both readability and maintainability while also making the algorithm easier to extend. Overall, the artifact was improved by making the brick generation process more structured, predictable, and aligned with gameplay considerations, rather than relying on uncontrolled randomness.

By restructuring the brick generation into a multi-stage algorithm, I demonstrated the ability to break down a problem into smaller, manageable steps and apply logic in a controlled and efficient way. The use of a 2D vector as the primary data structure allowed for constant-time access to grid elements and made it easier to enforce placement rules. I also considered trade-offs in my design. While more complex data structures (such as a map) could have been used, I chose a 2D vector because it provides a clear and efficient representation of the grid while maintaining readability. This decision balances performance with maintainability, which is important in real-world applications. At this stage, I believe the enhancement meets the intended course outcomes, so I do not have any major updates to the outcome coverage plan.

Working on the enhancement helped me better understand how important structure and planning are when designing algorithms. Initially, the system relied heavily on randomness, which made it unpredictable and harder to control. By introducing a structured approach, I was able to create more consistent and intentional behavior. One of the biggest things I learned was the value of separating responsibilities within an algorithm. Breaking the process into stages made the code much easier to reason about and debug. It also made it clearer where changes could be made without affecting the entire system.

A challenge I faced was finding the right balance between randomness and control. I wanted the grid to feel varied, but not unfair or restrictive. This required adding constraints, such as limiting consecutive wall placements and guaranteeing at least one breakable brick in the bottom row. Getting this balance right took some iteration and testing. Another challenge was making sure the code remained readable while adding more complexity. Introducing helper functions and clear comments helped address this and made the final implementation much cleaner.

Overall, this process strengthened my understanding of how to apply data structures and algorithm design to improve an existing system. It also reinforced the importance of writing code that is not only functional, but also maintainable and easy to understand.

---

## Supporting Materials

- [Original Artifact Components](https://github.com/clup-fishman/clup-fishman.github.io/tree/main/artifact2/original/)
- [Enhanced Artifact Components](https://github.com/clup-fishman/clup-fishman.github.io/tree/main/artifact2/enhanced/)
