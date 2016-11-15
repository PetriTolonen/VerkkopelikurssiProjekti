#include "Player.h"

Player::Player(b2Body* player_body, Tank_hull* t, Tank_turret* tt, float msf, float msb, float maf, float mab, float mmsf, float mmsb, float m, int mcd) : Object()
{
	this->player_body = player_body;
	this->t = t;
	this->tt = tt;
	turret_rotation_speed = tt->get_traverse_speed();
	hull_rotation_speed = t->get_traverse_speed();

	momentary_speed_forward = msf;
	momentary_max_speed_backward = msb;
	momentary_acceleration_forward = maf;
	momentary_acceleration_backward = mab;
	momentary_max_speed_forward = mmsf;
	momentary_max_speed_backward = mmsb;
	momentum = m;
	momentary_cooldown = mcd;

	health = 100;

	animation_has_played = false;
}

Player::~Player(void)
{

}

void Player::update(sf::Event event, sf::RenderWindow* win)
{

}

void Player::on_update(sf::Event event, sf::RenderWindow* win)
{
	if (health > 0)
	{
		////----turret_to_mouse----//

		sf::Vector2i pixel_pos = sf::Mouse::getPosition(*win);
		sf::Vector2f coord_pos = win->mapPixelToCoords(pixel_pos);

		float dx = x - coord_pos.x;
		float dy = y - coord_pos.y;
		float rotation = (atan2(dy, dx)) * 180 / M_PI;

		float rotation2 = (rotation + 180) - tt->get_rotation();

		if (rotation2 < 0)
		{
			rotation2 += 360;
		}

		//If tank turret close to mouse rotation set exactly to mouse rotation
		if (rotation2 < 180 + 0.6 && rotation2 > 180 - 0.6)
		{
			tt->get_sprite().setRotation(rotation);
		}
		else
		{
			if (rotation2 > 180)
			{
				tt->get_sprite().rotate(tt->get_traverse_speed() * 10 * _elapsed);

			}
			if (rotation2 < 180)
			{
				tt->get_sprite().rotate(-tt->get_traverse_speed() * 10 * _elapsed);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			momentary_acceleration_forward = t->get_acceleration_forward();
			momentary_max_speed_forward = t->get_max_speed_forward();
			momentary_speed_forward += _elapsed *momentary_acceleration_forward; //_elapsed



			if (momentary_speed_forward > momentary_max_speed_forward)
			{
				momentary_speed_forward = momentary_max_speed_forward;
			}

			player_body->SetLinearVelocity(b2Vec2(sin(player_body->GetAngle())*-momentary_speed_forward, cos(player_body->GetAngle())*momentary_speed_forward));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			momentary_acceleration_backward = tank_hull.get_acceleration_backward();
			momentary_max_speed_backward = tank_hull.get_max_speed_backward();
			momentary_speed_backward += _elapsed * momentary_acceleration_backward;

			if (momentary_speed_backward > momentary_max_speed_backward)
			{
				momentary_speed_backward = momentary_max_speed_backward;
			}
			player_body->SetLinearVelocity(b2Vec2(sin(player_body->GetAngle())*momentary_speed_backward, cos(player_body->GetAngle())*-momentary_speed_backward));
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player_body->SetAngularVelocity(hull_rotation_speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player_body->SetAngularVelocity(-hull_rotation_speed);

		}
	}
	//---Setting_sprite_postion---//
	set_position(player_body->GetPosition().x, player_body->GetPosition().y);
	//----------------------------//

	//---Setting_sprite_rotation---//
	t->get_sprite().setRotation((player_body->GetAngle() * (180.0f / M_PI)));
	//-----------------------------//

}

void Player::set_position(float x, float y)
{
	this->x = x*30.0;
	this->y = y*30.0;

	t->set_position(this->x, this->y);
	tt->set_position(this->x, this->y);

}

float Player::rotate(float rotation_speed)
{
	return 0;

}

sf::Vector2f Player::get_position()
{
	sf::Vector2f location(player_body->GetPosition().x*30.0, player_body->GetPosition().y*30.0);
	return location;
}

void Player::on_draw(sf::RenderWindow* win)
{
	if (health <= 0)
	{
		t->get_sprite().setColor(sf::Color(20, 20, 20));
		tt->get_sprite().setColor(sf::Color(20, 20, 20));
	}
	t->on_draw(win);
	tt->on_draw(win);
}

void Player::set_rotation(float rot)
{
	//rotation = rot;
}

float Player::get_rotation()
{
	return player_body->GetAngle();
}

sf::Vector2f Player::get_distance_traveled()
{
	return distance_traveled;
}

int Player::get_cooldown()
{
	return momentary_cooldown;
}

bool Player::get_can_fire()
{
	if (momentary_cooldown <= 0)
	{
		can_fire = true;
	}
	else
	{
		can_fire = false;
	}

	return can_fire;
}

void Player::set_cooldown()
{
	momentary_cooldown = tt->get_cooldown();
}

void Player::reduce_cooldown(int amount)
{
	momentary_cooldown -= amount;
}


float Player::get_rotation_turret()
{
	return tt->get_sprite().getRotation();
}


b2Body* Player::get_body()
{
	return player_body;
}

void Player::set_body_position(float x, float y)
{
}

void Player::set_animation_has_played()
{
	animation_has_played = true;
}

int Player::get_health()
{
	return health;
}

bool Player::get_has_animation_played()
{
	return animation_has_played;
}

void Player::reduce_health(int amount)
{
	health -= amount;
}