Feature: create pile
  As a comic creator
  I want to create a pile
  so that I can group some panels together
  without committing to stricter groupings like page, book etc.

  Background:
    Given the current workspace exists

  Scenario: completed
    Given no pile with name "pile1" exists in the current workspace
    When I create a pile with name "pile1"
    Then the pile with name "pile1" is created
    And I can lookup "pile1" in the current workspace

  Scenario: abandoned - pile already exists
    Given a pile with name "pile1" exists in the current workspace
    When I create a pile with name "pile1"
    Then the pile with name "pile1" is not created
    And I am told that a pile with name "pile1" already exists
