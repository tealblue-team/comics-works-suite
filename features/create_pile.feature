Feature: create pile
  As a comic creator
  I want to create a pile
  so that I can group some panels together
  without committing to stricter groupings like page, book etc.

  Background:
    Given the current workspace exists

  Scenario: completed
    Given no pile with name "someId" exists in the current workspace
    When I create a pile with name "someId"
    Then the pile with name "someId" is created
    And I can lookup "someId" in the current workspace

  Scenario: abandoned - pile already exists
    Given a pile with name "someId" exists in the current workspace
    When I create a pile with name "someId"
    Then the pile with name "someId" is not created
    And I am told that a pile with name "someId" already exists
