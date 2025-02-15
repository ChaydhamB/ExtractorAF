# File Conversion and Processing Project

This project is designed to process text files containing ICT log data, convert them into CSV format, and handle different file processing tasks, including single file and batch processing. It also includes a utility for exporting failed tests and a set of console-based navigation and animations.

## Overview

The program reads ICT log files, extracts data from specific fields, and outputs the results in a CSV format. The program supports:
- **Single file processing**: Convert individual files into CSV format.
- **Batch file processing**: Convert all `.txt` files in a specified directory to CSV.
- **Export failed tests**: Optionally export only failed test results into a separate CSV file.
- **Menu-driven interface**: Navigate between different actions using a simple console menu.

## Features

- **File Parsing**: Reads the ICT logs, filters valid lines, and parses data based on predefined fields.
- **CSV Generation**: Converts valid data into a CSV format for easy viewing and further analysis.
- **Failed Test Export**: Users can choose to export only failed tests or the entire test data.
- **File Extension Conversion**: Automatically changes the file extension from `.txt` to `.csv`.
- **Interactive Menu**: Users interact with the program through a navigation menu with various options.
- **Cross-platform Support**: Compatible with both Windows and Linux systems (due to the use of `windows.h` for `Sleep` and `unistd.h` for `usleep`).

## Prject structure

   ```bash
├── main.c                # Main program that drives the file processing logic
├── parser.c              # Contains functions for parsing, file processing, and exporting results
├── parser.h              # Header file for parser.c
├── menu.c                # Provides the menu interface for the user
├── animation.c           # Contains animations (e.g., loading screen)
├── navigation.c          # Handles navigation logic for the user menu
├── file_utils.c          # Contains file utility functions like change_extension_to_csv
└── README.md             # Project documentation



