# Advanced Calendar & Task Management System Using Google App Script Services

## Overview
This project is a comprehensive suite of Google Apps Script functions designed to automate and streamline the management of various types of events and tasks. The scripts interact with Google Sheets and Google Calendar, providing an integrated solution for handling internship events, academic deadlines, personal activities, extracurricular engagements, and college events. The system ensures efficient scheduling, reminders, and task tracking, offering a robust tool for personal and academic organization.

## Features
### 1.Automated Event Synchronization: 
Integrates with Google Calendar to automatically create and update events from Google Sheets data for different categories like internships, personal activities, extracurriculars, and college events.

### 2.Dynamic Task Management
Employs custom scripts to manage tasks and assignments within Google Sheets, including functionality to add tasks to Google Tasks, check and delete rows based on due dates and completion status, and clear completed tasks.

### 3.Efficient Data Processing
Incorporates advanced data manipulation techniques to clear past events and adjust task and event listings dynamically based on date and status changes.

### 4.Customizable Event Types
Supports various event types including all-day events and specific time events, with custom fields like event names, dates, and additional notes.

### 5.Logging and Vaidation
Includes error handling and logging to track script execution and ensure data integrity.

### 6.Timed-Execution
Includes automated timed executions that will run each function in the code once a certain condition is met

## Usage
Each function in the script is designed to be executed either manually or can be set up to run at scheduled intervals using Google Apps Script's triggers.

### createInternshipCalendarEvent()
Adds internship events from the sheet to the calendar.

### checkAndDeleteRows()
Cleans up outdated or completed tasks.

### clearCompletedTasks()
Removes tasks marked as 'Completed'.

### clearPastEvents()
Clears past events to keep the sheet up-to-date.

### createGoogleTasksFromSheet()
Syncs tasks from the sheet to Google Tasks.

### createEventFromExtracirricular(), createEventFromSheetPersonal(), createEventFromSheetCollegeEvents()
Different functions for adding specific types of events to the calendar.

### addEventsToAcademicCalendar()
Manages Academic Assignments and deadlines
