Feature: describe panel
  As a comic creator
  I want to describe a panel
  so that I can give it a meaning even before filling it

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created

  Scenario: completed
    When I try to describe panel "panel1" as "my first panel"
    Then a description is added to panel "panel1"
    And the description for panel "panel1" reads "my first panel"
