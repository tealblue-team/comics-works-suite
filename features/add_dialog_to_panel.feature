Feature: add dialog to panel
  As a comic creator
  I want to add a dialog to a panel
  so that I can convey story through language

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created
    And I try to create a character with name "Ayran"
    And the character with name "Ayran" is created
    And I try to add character with name "Ayran" to panel "panel1"
    And the character with name "Ayran" is added to panel "panel1"

  Scenario: completed
    When I try to add a dialog with id "dialog1" saying "hello world" for character "Ayran" to panel "panel1"
    Then a dialog with id "dialog1" is added to panel "panel1"
    And the first dialog for panel "panel1" belongs to character "Ayran"
    And the first dialog for panel "panel1" reads "hello world"
