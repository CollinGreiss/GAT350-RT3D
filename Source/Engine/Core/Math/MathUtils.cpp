#include "MathUtils.h"

namespace nc {

	glm::vec3 QuaternionToEuler( const glm::quat& q ) {

		glm::vec3 euler;

		float unit = ( q.x * q.x ) + ( q.y * q.y ) + ( q.z * q.z ) + ( q.w * q.w );

		float test = q.x * q.w - q.y * q.z;

		if ( test > 0.4995f * unit ) {

			euler.x = Pi / 2;
			euler.y = 2.0f * std::atan2( q.y, q.x );

			euler.z = 0;
		} else if ( test < -0.4995f * unit ) {

			euler.x = -Pi / 2;
			euler.y = -2.0f * std::atan2( q.y, q.x );
			euler.z = 0;

		} else {

			euler.x = std::asin( 2.0f * ( q.w * q.x - q.y * q.z ) );
			euler.y = std::atan2( 2.0f * q.w * q.y + 2.0f * q.z * q.x, 1 - 2.0f * ( q.x * q.x + q.y * q.y ) );
			euler.z = std::atan2( 2.0f * q.w * q.z + 2.0f * q.x * q.y, 1 - 2.0f * ( q.z * q.z + q.x * q.x ) );

		}

		euler = glm::degrees( euler );

		euler = glm::modf( glm::vec3{ 360.0f }, euler );

		return euler;

	}

	glm::quat EulerToQuaternion( const glm::vec3& euler ) {

		float xOver2 = glm::radians( euler.x ) * 0.5f;
		float yOver2 = glm::radians( euler.y ) * 0.5f;
		float zOver2 = glm::radians( euler.z ) * 0.5f;

		float sinXOver2 = std::sin( xOver2 );
		float cosXOver2 = std::cos( xOver2 );
		float sinYOver2 = std::sin( yOver2 );
		float cosYOver2 = std::cos( yOver2 );
		float sinZOver2 = std::sin( zOver2 );
		float cosZOver2 = std::cos( zOver2 );

		glm::quat result;
		result.x = cosYOver2 * sinXOver2 * cosZOver2 + sinYOver2 * cosXOver2 * sinZOver2;
		result.y = sinYOver2 * cosXOver2 * cosZOver2 - cosYOver2 * sinXOver2 * sinZOver2;
		result.z = cosYOver2 * cosXOver2 * sinZOver2 - sinYOver2 * sinXOver2 * cosZOver2;
		result.w = cosYOver2 * cosXOver2 * cosZOver2 + sinYOver2 * sinXOver2 * sinZOver2;

		return result;

	}

}