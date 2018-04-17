Feature: delete panel
  As a comic creator
  I want to delete a panel
  because I created too many.

  Background:
    Given I try to create a workspace with name "workspace1"
    And the workspace with name "workspace1" is created
    And I try to create a panel with name "panel1"
    And the panel with name "panel1" is created

  Scenario: completed
    When I try to delete a panel with name "panel1"
    Then the panel with name "panel1" is deleted
    And I cannot lookup the panel with name "panel1" in the current workspace
