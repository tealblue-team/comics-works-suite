Feature: delete project
  As a comic creator
  I want to delete a project
  to work on another project

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created
    And I try to create a character with name "Ayran"
    And the character with name "Ayran" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created
    And I try to add character with name "Ayran" to panel "panel1"
    And the character with name "Ayran" is added to panel "panel1"
    And I try to add a dialog with id "dialog1" saying "hello world" for character "Ayran" to panel "panel1"
    And a dialog with id "dialog1" is added to panel "panel1"

  Scenario: completed
    When I try to delete the project with id "project1"
    Then the project with id "project1" is deleted
    And the character with name "Ayran" is deleted
    And all dialogs for character with name "Ayran" in all panels are deleted
    And the character with name "Ayran" is deleted from all panels
    And I cannot lookup the panel with id "panel1" in the current project
