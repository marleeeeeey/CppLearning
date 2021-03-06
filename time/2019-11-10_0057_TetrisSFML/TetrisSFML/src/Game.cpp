#include  "Game.h"

Game::Game(sf::Vector2u size)
    : m_matrix(size)
{
    m_lastTimeStemp = clock.getElapsedTime();
    m_nextObject.setPos({size.x + 3, 1});
    m_object.setPos({1, 0});
    unsigned topOffset = 5;
    m_info.setPos({size.x + 3, topOffset});
    m_info.setLinesNumber(size.y - topOffset);
    m_isAccelerate = false;
    m_isPause = false;
}

void Game::draw(sf::RenderWindow& window)
{
    auto currentTime = clock.getElapsedTime();
    auto timeDiff = currentTime - m_lastTimeStemp;
    sf::Time period = sf::seconds(0.5);
    if (m_isAccelerate)
        period = sf::seconds(0.05f);
    if (timeDiff > period && !m_isPause)
    {
        auto moved = m_object.getMoved(0, +1);
        bool isCollision = m_matrix.checkCollision(moved);
        if (isCollision)
        {
            m_matrix.add(m_object);
            m_info.setScope(m_matrix.getRemovedLineCounter());
            m_object.setShape(m_nextObject.getShape());
            m_object.setPos({1, 0});
            bool isCollisionWithNewObject = m_matrix.checkCollision(m_object);
            if (isCollisionWithNewObject)
            {
                onGameOver();
            }
            m_nextObject.generateShape();
        }
        else
        {
            m_object = moved;
        }

        m_lastTimeStemp = currentTime;
    }

    m_matrix.draw(window);
    m_object.draw(window);
    m_nextObject.draw(window);
    m_info.draw(window);
}

bool isKeyPressed(sf::Event event, sf::Keyboard::Key key)
{
    return (event.type == sf::Event::EventType::KeyPressed
        && event.key.code == key);
}

void Game::dispatchKey(sf::Event event)
{
    if (isKeyPressed(event, sf::Keyboard::Key::Space))
    {
        m_isPause = !m_isPause;
    }

    if (m_isPause)
    {
        return;
    }

    if (isKeyPressed(event,sf::Keyboard::Left))
    {
        auto moved = m_object.getMoved(-1, 0);
        if (!m_matrix.checkCollision(moved))
            m_object = moved;
    }

    if (isKeyPressed(event, sf::Keyboard::Right))
    {
        auto moved = m_object.getMoved(+1, 0);
        if (!m_matrix.checkCollision(moved))
            m_object = moved;
    }

    if (isKeyPressed(event, sf::Keyboard::Down))
    {
        m_isAccelerate = true;
    }
    else
    {
        m_isAccelerate = false;
    }

    if (isKeyPressed(event, sf::Keyboard::Up))
    {
        auto rotateObject = m_object.getRotateObject();
        bool isCollision = m_matrix.checkCollision(rotateObject);

        if (!isCollision)
        {
            m_object = rotateObject;
        }
        else
        {
            int maxObjectDemension = 4;
            for (int i = 1; i < maxObjectDemension; ++i)
            {
                auto movedToLeft = rotateObject.getMoved(-i, 0);
                bool isRightCollision = m_matrix.checkCollision(movedToLeft);
                if (!isRightCollision)
                {
                    m_object = movedToLeft;
                    break;
                }
            }
        }
    }
}

void Game::onGameOver()
{
    m_info.fixScope();
    m_matrix.clear();
}
