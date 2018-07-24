Feature: name project
  As a comic creator
  I want to name a project
  so that I can refer to it easily

  Background:
    Given I try to create a project with id "project1"
    And the project with id "project1" is created

  Scenario: completed
    When I try to name project "project1" as "my project"
    Then a name is added to project "project1"
    And the name for project "project1" reads "my project"
