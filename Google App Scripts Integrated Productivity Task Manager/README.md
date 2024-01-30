# Advanced Calendar & Task Management System Using Google App Script Services

## Overview
This project is a comprehensive suite of Google Apps Script functions designed to automate and streamline the management of various types of events and tasks. The scripts interact with Google Sheets and Google Calendar, providing an integrated solution for handling internship events, academic deadlines, personal activities, extracurricular engagements, and college events. The system ensures efficient scheduling, reminders, and task tracking, offering a robust tool for personal and academic organization.

## Features
- **Automated Event Synchronization:** Integrates with Google Calendar to automatically create and update events from Google Sheets data for different categories like internships, personal activities, extracurriculars, and college events.

- **Dynamic Task Management:** Employs custom scripts to manage tasks and assignments 
within Google Sheets, including functionality to add tasks to Google Tasks, check and delete rows based on due dates and completion status, and clear completed tasks.

- **Efficient Data Processing:** Incorporates advanced data manipulation techniques to clear past events and adjust task and event listings dynamically based on date and status changes.

- **Customizable Event Types:** Supports various event types including all-day events and specific time events, with custom fields like event names, dates, and additional notes.

- **Logging and Validation:** Includes error handling and logging to track script execution and ensure data integrity.

- **Timed-Execution:** Features automated timed executions that run each function in the code when certain conditions are met.

## Innovative Task Management Through Google Tasks API Integration and Connectivity

In this project, a key feature is the innovative use of the Google Tasks API, which plays a pivotal role in managing tasks and task lists directly from Google Sheets. This integration facilitates a dynamic and real-time reflection of tasks in the user's personal Google Calendar, thereby offering a seamless and automated workflow for task tracking and management.

### How it Works:

- **Task Synchronization**: The system utilizes the Google Tasks API to synchronize tasks listed in a Google Sheet with the user's Google Tasks. This ensures that any addition, modification, or deletion of tasks in the spreadsheet is automatically reflected in Google Tasks.

- **Calendar Reflection**: Tasks synchronized with Google Tasks are then automatically displayed on the user's Google Calendar. This integration provides a comprehensive view of tasks alongside events, enhancing time management and planning.

- **Custom Scripting**: Custom scripts are written in Google Apps Script to facilitate this integration. These scripts handle the communication between Google Sheets, Google Tasks API, and Google Calendar, offering a streamlined and efficient task management process.

- **Real-Time Updates**: The system is designed to update tasks in real time. When a task is marked as completed, or its details are modified in Google Sheets, these changes are instantly reflected in both Google Tasks and the user's calendar.

- **User-Friendly Interface**: All these functionalities are presented through a user-friendly interface in Google Sheets, allowing users to manage their tasks without needing to navigate away from their spreadsheet environment.

### Benefits:

- **Enhanced Productivity**: This integration significantly boosts productivity by automating the task management process, reducing the need for manual entry and updates.
- **Unified System**: Users benefit from a unified system for managing both their calendar events and tasks, all within a single interface.
- **Accessibility**: With tasks and events consolidated in one place, users have easy access to their schedules, making it simpler to plan and prioritize their time.

## Usage
Each function in the script is designed to be executed either manually or can be set up to run at scheduled intervals using Google Apps Script's triggers.

- **createInternshipCalendarEvents():** Adds internship events from the sheet to the calendar.

- **checkAndDeleteRows():** Cleans up outdated or completed tasks.

- **clearCompletedTasks():** Removes tasks marked as 'Completed'.

- **clearPastEvents():** Clears past events to keep the sheet up-to-date.

- **createGoogleTasksFromSheet():** Syncs tasks from the sheet to Google Tasks.

- **createEventFromExtracirricular(), createEventFromSheetPersonal(), createEventFromSheetCollegeEvents():** Different functions for adding specific types of events to the calendar.

- **addEventsToAcademicCalendar():** Manages academic assignments and deadlines.

## Implementations (w/pictures)
![image](https://github.com/kaushikvada3/Projects/assets/58670585/c1c80644-badc-4117-9abe-b4684bbd004c)

![Screenshot 2024-01-28 182512](https://github.com/kaushikvada3/Projects/assets/58670585/f29f768d-5736-41d4-a39a-86304d1c1aff)

![image](https://github.com/kaushikvada3/Projects/assets/58670585/8184e9e9-4c92-43db-bb0e-e1af892232a6)
