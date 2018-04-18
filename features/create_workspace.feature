Feature: create workspace
  As a comic creator
  I want to create a workspace
  so that I can keep all related work and settings in one place

  Scenario: success
    Given no workspace with name "workspace1" exists
    When I try to create a workspace with name "workspace1"
    Then the workspace with name "workspace1" is created
