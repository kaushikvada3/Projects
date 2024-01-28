function createInternshipCalendarEvents() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Kaushik Vada - Internships");
  var data = sheet.getDataRange().getValues();
  
  // Get the "Internships/Applications" calendar by its name.
  var calendar = CalendarApp.getCalendarsByName("Internships/Applications")[0];
  
  if (!calendar) {
    throw new Error('Internships/Applications calendar not found');
  }

  for (var i = 1; i < data.length; i++) {
    var eventName = data[i][0]; // Column A
    var eventDate = new Date(data[i][3]); // Column D
    var eventDescription = data[i][5]; // Column F
  
    var eventOptions = {
      description: eventDescription
    };
  
    // Check if the event already exists before creating it.
    var eventsOnDate = calendar.getEventsForDay(eventDate);
    var eventExists = false;
  
    for (var j = 0; j < eventsOnDate.length; j++) {
      if (eventsOnDate[j].getTitle() === eventName) {
        eventExists = true;
        break;
      }
    }
  
    if (!eventExists) {
      calendar.createAllDayEvent(eventName, eventDate, eventOptions);
    }
  }
}


function checkAndDeleteRows() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Kaushik Vada - Overview");
  var range = sheet.getRange(3, 1, 18, 5);  // Starts from row 3 to 20 and from column A to E
  var values = range.getValues();
  
  var currentDate = new Date();
  currentDate.setHours(0, 0, 0, 0);  // Setting hours, minutes, and seconds to 0 for accurate comparison
  
  var newValues = [];  // This will store rows which are not to be deleted
  
  for (var i = 0; i < values.length; i++) {
    var dueDate = new Date(values[i][3]);  // Column D
    var status = values[i][4];  // Column E
    
    if (dueDate > currentDate && status != "Completed") {
      newValues.push(values[i]);
    }
  }
  
  // Only clear and write back if newValues has elements
  if (newValues.length > 3) {
    range.clearContent();  // Clearing the entire range
    sheet.getRange(3, 1, newValues.length, 5).setValues(newValues);  // Writing back the rows
  }
}


function clearCompletedTasks() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Kaushik Vada - Overview");
  var dataRange = sheet.getRange("A24:G37"); // Extended the range to include column G
  var values = dataRange.getValues();
  var isChanged = false;
  
  // Loop through rows in the data range
  for (var i = 0; i < values.length; i++) {
    // Check if the status (Column D) is 'Completed'
    if (values[i][3] == "Completed") {
      // Shift rows up
      for(var j = i; j < values.length - 1; j++) {
        values[j] = values[j + 1];
      }
      // Clear the last row's values
      values[values.length - 1] = ["", "", "", "", "", "", ""];
      isChanged = true;
    }
  }
  
  // If any changes were made, update the sheet with new values.
  if (isChanged) {
    dataRange.setValues(values);
  }
}




function clearPastEvents() {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName("Kaushik Vada - Overview");
  var range = sheet.getRange(3, 9, 18, 8); // Rows 3 to 20, Columns I to O
  var values = range.getValues();
  
  var today = new Date();
  today.setHours(0,0,0,0); // Set time to midnight for accurate comparison

  // Loop through each row in the range from bottom to top
  for (var i = values.length - 1; i >= 0; i--) {
    var eventDate = new Date(values[i][0]); // Date is in the first column of the range (Column I)
    if (eventDate < today) {
      // Shift every row below this one up
      if (i < values.length - 1) { // Check if it's not the last row
        var rangeToMove = sheet.getRange(i + 4, 9, values.length - (i + 1), 8); // Rows below the current one, Columns I to O
        var destination = sheet.getRange(i + 3, 9); // Destination starts from current row, Column I
        rangeToMove.moveTo(destination);
      }
      // Clear the last row as it has been duplicated
      sheet.getRange(values.length + 2, 9, 1, 8).clearContent(); // The last row in the range
    }
  }
}



function createGoogleTasksFromSheet() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Kaushik Vada - Overview");
  var data = sheet.getRange("A24:G37").getValues();
  
  data.forEach(function(row) {
    var taskTitle = row[0];
    var dueDate = row[2];
    var notes = row[4] + (row[5] ? " " + row[5] : ""); // Append the value from column F if it's not empty.
    var addedToCalendar = row[6]; 
    
    // Ensure there's a task name, due date, and it hasn't been added to calendar yet.
    if (taskTitle && dueDate && !addedToCalendar) {
      createTask(taskTitle, dueDate, notes);
      // Mark the task as added to calendar.
      sheet.getRange("G" + (24 + data.indexOf(row))).setValue("Yes");
    }
  });
}

function createTask(title, dueDate, notes) {
  var taskListId = getFirstTaskListId();
  
  if (taskListId) {
    var task = {
      title: title,
      due: dueDate.toISOString(),
      notes: notes
    };

    Tasks.Tasks.insert(task, taskListId);
  } else {
    Logger.log("No task lists found.");
  }
}

function getFirstTaskListId() {
  var taskLists = Tasks.Tasklists.list();
  if (taskLists.items && taskLists.items.length > 0) {
    return taskLists.items[0].id;
  }
  return null;
}

function createEventFromSheetExtracirricular() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName('Kaushik Vada - Overview');
  if (!sheet) {
    Logger.log('Sheet not found');
    return;
  }
  
  var range = sheet.getRange(3, 9, 18, 8); // Adjust as needed
  var values = range.getValues();
  
  // Accessing the Calendar
  var calendars = CalendarApp.getCalendarsByName('Extracirriculars and clubs');
  if (calendars.length === 0) {
    Logger.log('Calendar not found');
    return;
  }
  var calendar = calendars[0];
  
  for (var i = 0; i < values.length; i++) {
    var row = values[i];
    
    var date = row[0];
    var type = row[1];
    var eventName = row[2];
    var location = row[3];
    var startTime = row[4];
    var endTime = row[5];
    var notes = row[6] + ' ' + row[7];
    
    if (type === "Extracirricular" && date && startTime && endTime) {
      var startDateTime = new Date(date);
      startDateTime.setHours(startTime.getHours(), startTime.getMinutes(), 0);
      
      var endDateTime = new Date(date);
      endDateTime.setHours(endTime.getHours(), endTime.getMinutes(), 0);

      var existingEvents = calendar.getEvents(startDateTime, endDateTime, {
        search: eventName
      });

      var eventExists = existingEvents.some(function(event) {
        return event.getTitle() === eventName;
      });

      if (!eventExists) {
        var event = calendar.createEvent(eventName, startDateTime, endDateTime, {
          description: notes,
          location: location
        });
        Logger.log('Event created: ' + event.getTitle());
      } else {
        Logger.log('Event already exists: ' + eventName);
      }
    }
  }
}

function createEventFromSheetPersonal() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName('Kaushik Vada - Overview');
  var range = sheet.getRange(3, 9, 18, 8); // Adjust as needed
  var values = range.getValues();
  
  // Accessing the Calendar
  var calendar = CalendarApp.getCalendarsByName('Personal Activities')[0];
  
  for (var i = 0; i < values.length; i++) {
    var row = values[i];
    
    var date = row[0];
    var type = row[1];
    var eventName = row[2];
    var location = row[3];
    var startTime = row[4];
    var endTime = row[5];
    var notes = row[6] + ' ' + row[7]; // O & P are merged
    
    if (type === "Personal") {
      // Combining date and start time for event start datetime
      var startDateTime = new Date(date);
      startDateTime.setHours(startTime.getHours(), startTime.getMinutes(), 0);
      
      // Combining date and end time for event end datetime
      var endDateTime = new Date(date);
      endDateTime.setHours(endTime.getHours(), endTime.getMinutes(), 0);

      // Check if the event already exists
      var existingEvents = calendar.getEvents(startDateTime, endDateTime, {
        search: eventName
      });

      var eventExists = false;
      for (var j = 0; j < existingEvents.length; j++) {
        if (existingEvents[j].getTitle() === eventName) {
          eventExists = true;
          break;
        }
      }

      if (!eventExists) {
        // Create the event if it doesn't exist
        var event = calendar.createEvent(eventName, startDateTime, endDateTime, {
          description: notes,
          location: location
        });
        
        Logger.log('Event created: ' + event.getTitle());
      } else {
        Logger.log('Event already exists: ' + eventName);
      }
    }
  }
}

function createEventFromSheetCollegeEvents() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName('Kaushik Vada - Overview');
  var range = sheet.getRange(3, 9, 18, 8); // Adjust as needed
  var values = range.getValues();
  
  // Accessing the Calendar
  var calendar = CalendarApp.getCalendarsByName('College Events')[0];
  
  for (var i = 0; i < values.length; i++) {
    var row = values[i];
    
    var date = row[0];
    var type = row[1];
    var eventName = row[2];
    var location = row[3];
    var startTime = row[4];
    var endTime = row[5];
    var notes = row[6] + ' ' + row[7]; // O & P are merged
    
    if (type === "College/Career Events") {
      // Combining date and start time for event start datetime
      var startDateTime = new Date(date);
      startDateTime.setHours(startTime.getHours(), startTime.getMinutes(), 0);
      
      // Combining date and end time for event end datetime
      var endDateTime = new Date(date);
      endDateTime.setHours(endTime.getHours(), endTime.getMinutes(), 0);

      // Check if the event already exists
      var existingEvents = calendar.getEvents(startDateTime, endDateTime, {
        search: eventName
      });

      var eventExists = false;
      for (var j = 0; j < existingEvents.length; j++) {
        if (existingEvents[j].getTitle() === eventName) {
          eventExists = true;
          break;
        }
      }

      if (!eventExists) {
        // Create the event if it doesn't exist
        var event = calendar.createEvent(eventName, startDateTime, endDateTime, {
          description: notes,
          location: location
        });
        
        Logger.log('Event created: ' + event.getTitle());
      } else {
        Logger.log('Event already exists: ' + eventName);
      }
    }
  }
}

function addEventsToAcademicCalendar() {
    var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName('Kaushik Vada - Overview');
    var calendar = CalendarApp.getCalendarsByName('Assignments')[0]; // Assuming 'Assignments' is the exact name of your calendar

    // Adjust the range according to your needs.
    var range = sheet.getRange(3, 1, 18, 6);
    var values = range.getValues();

    values.forEach(function (row) {
        var assignmentName = row[0];
        var classSubject = row[1];
        var type = row[2];
        var dueDate = row[3];
        var status = row[4];
        var notes = row[5];

        // Check if the mandatory fields are not empty
        if (assignmentName && classSubject && type && dueDate && status !== 'Completed') {
            var title = `${classSubject}: ${assignmentName} (${type})`;

            if (Object.prototype.toString.call(dueDate) === '[object Date]') { // Validate if the dueDate is a Date object
                var eventExists = calendar.getEventsForDay(dueDate, {
                    search: title
                }).length > 0;

                if (!eventExists) {
                    // Check whether a time is associated with the due date
                    if (dueDate.getHours() === 0 && dueDate.getMinutes() === 0) { // All day event
                        calendar.createAllDayEvent(title, dueDate, {
                            description: notes
                        });
                    } else { // Specific time event
                        var endDate = new Date(dueDate);
                        endDate.setHours(endDate.getHours() + 1);
                        calendar.createEvent(title, dueDate, endDate, {
                            description: notes
                        });
                    }
                }
            }
        }
    });
}