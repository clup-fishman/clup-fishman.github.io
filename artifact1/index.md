---
layout: default
title: Artifact One
page-nav:
  - id: art1-narrative
    label: Narrative
  - id: art1-supporting-materials
    label: Supporting Materials
---

<h1 class="center-text">Artifact One: Software Design and Engineering</h1>

{% include page-nav.html links=page.page-nav %}

<img
  src="{{ '/assets/images/art1_screen.png' | relative_url }}"
  alt="Travlr Admin Portal"
  class="project-image">

<img
  src=" '/assets/images/art1_screen2.png' | relative_url }}"
  alt="Travlr Destination Page"
  class="project-image">

<div id="art1-narrative"></div>
## Narrative

The artifact selected for this enhancement is the Travlr MEAN stack application from the CS-465 Full-Stack Development course. As the course name suggests, this is a full-stack web application that includes a customer-facing frontend using Node and Express, and an administrative interface that utilizes Angular. Both interact with a MongoDB database. The primary purpose of the application is to manage travel packages, allowing users to view trips and administrators to manage travel packages by creating or updating the trip data through authenticated API endpoints. This artifact was originally the baseline for an application that included functionality for routing, database interaction, and user authentication. However, much of the implementation followed a more direct and less modular approach, particularly with the backend architecture.

I selected this artifact because it provides a strong foundation for demonstrating software engineering and design principles in a real-world full-stack application. It includes both frontend and backend components, which allowed me to focus on improving system architecture, maintainability, and code organization.

The backend portion of the application offered several opportunities for enhancement. Originally, much of the logic was tightly coupled with authentication, validation, and database operations handled directly within route handlers and controllers. This made the code harder to maintain and less scalable.

With this enhancement, I was able to demonstrate key skills such as separation of concerns, modular design, and improved error handling. The updated structure introduces middleware for authentication and validation, a service layer for database interactions, and centralized error handling. These changes significantly improve the readability and maintainability of the application while aligning more closely with industry best practices.

There were several key improvements made to the application to improve its overall design and architecture. One of the primary enhancements was the introduction of middleware to handle authentication and request validation. JWT authentication logic was moved out of the routes and into a dedicated middleware module, making it reusable and easier to manage. In addition, a validation middleware was added to ensure that required trip data is present before processing requests. This helps prevent invalid data from reaching the database and reduces the complexity of the controller logic.

Another major improvement was the implementation of centralized error handling. The original application used nested and inconsistent error handling within the main application file. This was replaced with a single error handling middleware that processes both API and server-rendered errors in a consistent way. This approach improves maintainability and makes debugging more straightforward.

A service layer was also introduced to separate database operations from controller logic. Instead of interacting directly with the database, controllers now call functions defined in a dedicated service module. This creates clear separation between request handling and data access, making the code more modular and easier to extend in the future.

On the administrative frontend side, trip-data.service was refactored to remove hard-coded API URLs and use an environment-based configuration instead. This allows API endpoints to be managed in a centralized location, improving flexibility and making the application easier to adapt to different environments.

Finally, general code quality improvements were made, including consistent formatting, improved naming conventions, and the removal of unnecessary comments. While commenting in code is generally a good practice, good naming conventions should prevent excessive comments which can make code harder to read and congested. These changes directly align with readability and maintenance.

One of the first course outcomes these changes align with is the ability to design and evaluate computing solutions using appropriate practices. The introduction of middleware, a service layer, and centralized error handling reflects a more structured and scalable approach to application design.

Next, the improvements show the use of well-founded techniques and tools in computing practices. By restructuring the application to follow common architectural patterns, the overall quality and maintainability of the codebase was significantly improved.

Additionally, a security mindset was placed forward by improving authentication handling and validating input before processing requests. These changes reduce the risk of invalid or malicious data entering the system.

All these changes represent meaningful progress towards the pursuit of becoming a better engineer, while meeting the program outcomes and reflecting my strengthened understanding of software design principles.

The work on this enhancement gave me key insight into understanding of how proper software architecture impacts maintainability and scalability. The original application was functional, but it quickly became clear that the lack of separation between components limited the ease of growth in the system.

One of the main challenges was restructuring the application without breaking existing functionality. Introducing middleware and a service layer required careful updates to the request flow to ensure that all components worked together correctly. Debugging issues related to module paths and application structure also reinforced the importance of maintaining a consistent project organization.

Another key takeaway was the importance of designing with future scalability in mind. Modularizing the application and separating responsibilities better prepares the codebase for future enhancements and makes it easier for other developers to understand.

Overall, this strengthened my understanding of backend architecture, middleware design, and the complete structure of a full-stack application. This also highlighted the importance of writing clean, maintainable code that follows established best practices.

{% include back-button.html %}

---

<div id="art1-supporting-materials"></div>
## Supporting Materials

- [Original Artifact Components](https://github.com/clup-fishman/clup-fishman.github.io/tree/main/artifact1/original/)
- [Enhanced Artifact Components](https://github.com/clup-fishman/clup-fishman.github.io/tree/main/artifact1/enhanced/)
