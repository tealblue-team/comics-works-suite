Feature: add character to panel
  As a comic creator
  I want to add a character to a panel
  so that I can describe their actions and says

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created
    And I try to create a character with name "Ayran"
    And the character with name "Ayran" is created

  Scenario: completed
    When I try to add character with name "Ayran" to panel "panel1"
    Then the character with name "Ayran" is added to panel "panel1"
