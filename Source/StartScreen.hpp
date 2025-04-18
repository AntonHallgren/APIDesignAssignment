#pragma once


class StartScreen
{
	bool active = true;
public:
	void Update() noexcept;
	void Render() const noexcept;
	bool GetActive() const noexcept;
};