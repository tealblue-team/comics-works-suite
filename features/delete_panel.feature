Feature: delete panel
  As a comic creator
  I want to delete a panel
  because I created too many

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created

  Scenario: completed
    When I try to delete a panel with id "panel1"
    Then the panel with id "panel1" is deleted
    And I cannot lookup the panel with id "panel1" in the current project
