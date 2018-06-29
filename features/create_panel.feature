Feature: create panel
  As a comic creator
  I want to create a panel
  so that I can tell a story fragment through it

  Background:
    Given I try to create a project with name "project1"
    And the project with name "project1" is created

  Scenario: completed
    Given no panel with id "panel1" exists in the current project
    When I try to create a panel with id "panel1"
    Then the panel with id "panel1" is created
    And I can lookup the panel with id "panel1" in the current project
    And the width of panel "panel1" is greater than "0"
    And the height of panel "panel1" is greater than "0"

  Scenario: abandoned - panel already exists
    Given I try to create a panel with id "panel1"
    And a panel with id "panel1" exists in the current project
    When I try to create a panel with id "panel1"
    Then the panel with id "panel1" is not created
    And I am told that a panel with id "panel1" already exists
