Feature: name panel
  As a comic creator
  I want to name a panel
  so that I can refer to it according to my organisation system

  Background:
    Given I try to create a workspace with name "workspace1"
    And the workspace with name "workspace1" is created
    And I try to create a panel with id "panel1"
    And the panel with id "panel1" is created

  Scenario: completed
    When I try to name panel "panel1" as "HL-I-1"
    Then a name is added to panel "panel1"
    And the name for panel "panel1" reads "HL-I-1"
