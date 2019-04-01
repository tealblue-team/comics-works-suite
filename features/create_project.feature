Feature: create project
  As a comic creator
  I want to create a project
  so that I can keep all related work and settings in one place

  Scenario: success
    Given no project with id "project1" exists
    When I try to create a project with id "project1"
    Then the project with id "project1" is created
