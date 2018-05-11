Feature: delete character
  As a comic creator
  I want to delete a character
  because I changed my mind on cast

  Background:
    Given I try to create a workspace with name "workspace1"
    And the workspace with name "workspace1" is created
    And I try to create a character with name "Ayran"
    And the character with name "Ayran" is created
    And I try to create a panel with name "panel1"
    And the panel with name "panel1" is created
    And I try to add character with name "Ayran" to panel "panel1"
    And the character is added to panel "panel1"
    And I try to add a dialog saying "hello world" for character "Ayran" to panel "panel1"
    And a dialog is added to panel "panel1"

  Scenario: completed
    When I try to delete a character with name "Ayran"
    Then the character with name "Ayran" is deleted
    And I cannot lookup the character with name "Ayran" in the current workspace
    And the dialog saying "hello world" for character "Ayran" in panel "panel1" is deleted
    And the character with name "Ayran" in panel "panel1" is deleted
