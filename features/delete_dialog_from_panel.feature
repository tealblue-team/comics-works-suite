Feature: delete dialog from panel
  As a comic creator
  I want to delete a dialog from a panel
  so that I can improve the story

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created
    And I try to create a character with name "Ayran"
    And the character with name "Ayran" is created
    And I try to add character with name "Ayran" to panel "panel1"
    And the character with name "Ayran" is added to panel "panel1"
    And I try to add a dialog with id "dialog1" saying "hello world" for character "Ayran" to panel "panel1"
    And a dialog with id "dialog1" is added to panel "panel1"

  Scenario: completed
    When I try to delete the dialog with id "dialog1" from panel "panel1"
    Then the dialog "dialog1" is deleted from panel "panel1"
