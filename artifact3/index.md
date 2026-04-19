---
layout: default
title: Artifact Three
page-nav:
  - id: art3-narrative
    label: Narrative
  - id: art3-supporting-materials
    label: Supporting Materials
---

<h1 class="center-text">Artifact Three: Databases</h1>

{% include page-nav.html links=page.page-nav %}

<div id="art3-narrative"></div>
## Narrative

The artifact I selected for the databases enhancement is a Python-based dashboard application utilizing MongoDB to manage animal shelter data. This project was originally created during the CS-340 Client/Server Development class. This focuses on implementing a CRUD module to manage database operations and allow users to visualize the data with a Dash interface. The application allows users to view and filter animal records, interact with a data table, and visualize results through charts and a map. The dashboard dynamically updates based on user input, providing a more interactive way to explore the dataset.

I selected this artifact because it demonstrates my ability to work with databases, build a functional backend using Python, and connect that backend to a user interface. It highlights my understanding of CRUD operations, data handling, and how to present data in a meaningful way. What made this artifact especially valuable for my ePortfolio is that it provded a strong foundation to build on. While the original version worked as intended, it was mostly limited to basic data retrieval and display. This made it a good candidate for enhancement because I could expand it to include more advanced database features while improving both performance and usability.

The improvements I made focused on introducing aggregation capabilities, improving query performance, and refining the user interface. One of the key benefits of adding the aggregation pipeline was the ability to generate a summary of the animal outcome types throughout the dataset. This gives users a higher-level insight rather than only displaying raw records. I also added indexing to improve query efficiency and implemented better error handling, particularly in the map component where missing location data could previously cause issues. In addition, I reorganized the layout of the dashboard to create a clearer separation between overall dataset insights and filtered views. These changes made the application feel more intentional and easier to use.

Going into this enhancement, my goal was to strengthen my understanding of database design and demonstrate the ability to go beyond basic CRUD operations. I also wanted to show that I could improve an existing system by making it more efficient, more reliable, and more useful to the end user. I believe I met those goals. The use of aggregation pipelines demonstrates a more advanced approach to querying data, and the addition of indexing reflects an understanding of performance considerations. These changes align with the outcome of using well-founded techniques and tools to implement computing solutions that deliver value. I also made progress toward developing a security and reliability mindset by adding validation and guard conditions to prevent runtime issues. While this was not a full security overhaul, it shows an awareness of potential failure points and the importance of handling them properly. The original assignment relied on hardcoded credentials, so I refactored this to use environment variables to better reflect a production-ready and security conscious approach. At this point, I do not have major updates planned for my outcome coverage, but this enhancement reinforced that I am moving in the right direction, especially in the areas of database design and practical software improvement.

The biggest thing I learned from this process was how to take a working piece of software and push it further instead of just rebuilding something from scratch. It forced me to think more critically about what was missing and how to improve it in a meaningful way. One of the challenges I faced was deciding what enhancements actually added value. At one point, I had multiple charts showing similar information, which made the dashboard feel redundant. I had to step back and think about the purpose of each component and how it contributed to the overall experience. This led me to replace the original summary with a more meaningful aggregation that better aligned with the goals of the application. Another challenge was making sure the application remained stable while adding new functionality. For example, handling missing location data in the map required me to think about edge cases that were not originally considered. This reinforced the importance of defensive programming and building systems that can handle imperfect data.

Overall, this process helped me better understand how backend improvements like aggregation and indexing can directly impact the user experience when they are integrated properly. It also gave me more confidence in my ability to analyze existing code, identify weaknesses, and make targeted improvements that align with real-world development practices.

{% include back-button.html %}

---

<div id="art3-supporting-materials"></div>
## Supporting Materials

- [Original Artifact Components](https://github.com/clup-fishman/clup-fishman.github.io/tree/main/artifact3/original/)
- [Enhanced Artifact Components](https://github.com/clup-fishman/clup-fishman.github.io/tree/main/artifact3/enhanced/)
