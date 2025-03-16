import pytest
from unittest.mock import patch

from deposit import TimeDeposit


def test_time_deposit_initialization():
    deposit = TimeDeposit("Test Deposit", 5, (6, 18), (1000, 100000))
    assert deposit.name == "Test Deposit"
    assert deposit._interest_rate == 5
    assert deposit._period_limit == (6, 18)
    assert deposit._sum_limit == (1000, 100000)


def test_time_deposit_check_self():
    deposit = TimeDeposit("Test Deposit", 5, (6, 18), (1000, 100000))
    with pytest.raises(AssertionError):
        deposit._interest_rate = 0
        deposit._check_self()
    with pytest.raises(AssertionError):
        deposit._period_limit = (0, 1)
        deposit._check_self()
    with pytest.raises(AssertionError):
        deposit._sum_limit = (0, 1)
        deposit._check_self()


def test_time_deposit_check_user_params():
    deposit = TimeDeposit("Test Deposit", 5, (6, 18), (1000, 100000))
    with pytest.raises(AssertionError):
        deposit._check_user_params(500, 12)
    with pytest.raises(AssertionError):
        deposit._check_user_params(100001, 12)
    with pytest.raises(AssertionError):
        deposit._check_user_params(1000, 5)
    with pytest.raises(AssertionError):
        deposit._check_user_params(1000, 19)


def test_time_deposit_get_profit():
    deposit = TimeDeposit("Test Deposit", 5, (6, 18), (1000, 100000))
    assert deposit.get_profit(1000, 12) == 50


def test_time_deposit_get_sum():
    deposit = TimeDeposit("Test Deposit", 5, (6, 18), (1000, 100000))
    assert deposit.get_sum(1000, 12) == 1050
