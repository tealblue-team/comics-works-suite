Feature: delete character
  As a comic creator
  I want to delete a character
  because I changed my mind about the cast

  Background:
    Given I try to create a project with name "project1"
    And the project with name "project1" is created
    And I try to create a character with name "Ayran"
    And the character with name "Ayran" is created
    And I try to create a character with name "Birun"
    And the character with name "Birun" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created
    And I try to add character with name "Ayran" to panel "panel1"
    And the character with name "Ayran" is added to panel "panel1"
    And I try to add character with name "Birun" to panel "panel1"
    And the character with name "Birun" is added to panel "panel1"
    And I try to add a dialog saying "hi mate" for character "Birun" to panel "panel1"
    And a dialog is added to panel "panel1"
    And I try to add a dialog saying "hello world" for character "Ayran" to panel "panel1"
    And a dialog is added to panel "panel1"

  Scenario: completed
    When I try to delete the character with name "Ayran"
    Then the character with name "Ayran" is deleted
    And all dialogs for character with name "Ayran" in all panels are deleted
    And the character with name "Ayran" is deleted from all panels
