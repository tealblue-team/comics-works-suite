Feature: create character
  As a comic creator
  I want to create a character
  so that I can tell stories through them

  Background:
    Given I try to create a workspace with name "workspace1"
    And the workspace with name "workspace1" is created

  Scenario: completed
    Given no character with name "Ayran" exists in the current workspace
    When I try to create a character with name "Ayran"
    Then the character with name "Ayran" is created
    And I can lookup the character with name "Ayran" in the current workspace
