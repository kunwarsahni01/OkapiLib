/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/chassis/model/chassisModel.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/device/rotarysensor/continuousRotarySensor.hpp"

namespace okapi {
class SkidSteerModel : public ChassisModel {
  public:
  /**
   * Model for a skid steer drive (wheels parallel with robot's direction of motion). When all
   * motors are powered +100%, the robot should move forward in a straight line.
   *
   * @param ileftSideMotor left side motor
   * @param irightSideMotor right side motor
   * @param ileftEnc  left side encoder
   * @param irightEnc right side encoder
   */
  SkidSteerModel(std::shared_ptr<AbstractMotor> ileftSideMotor,
                 std::shared_ptr<AbstractMotor> irightSideMotor,
                 std::shared_ptr<ContinuousRotarySensor> ileftEnc,
                 std::shared_ptr<ContinuousRotarySensor> irightEnc,
                 double imaxVelocity,
                 double imaxVoltage);

  /**
   * Drive the robot forwards (using open-loop control). Uses velocity mode.
   *
   * @param ispeed motor power
   */
  void forward(double ispeed) override;

  /**
   * Drive the robot in an arc (using open-loop control). Uses velocity mode.
   * The algorithm is (approximately):
   *   leftPower = ySpeed + zRotation
   *   rightPower = ySpeed - zRotation
   *
   * @param iySpeed speed on y axis (forward)
   * @param izRotation speed around z axis (up)
   */
  void driveVector(double iySpeed, double izRotation) override;

  /**
   * Drive the robot in an arc. Uses voltage mode.
   * The algorithm is (approximately):
   *   leftPower = forwardSpeed + yaw
   *   rightPower = forwardSpeed - yaw
   *
   * @param iforwadSpeed speed in the forward direction
   * @param iyaw speed around the vertical axis
   */
  void driveVectorVoltage(double iforwardSpeed, double iyaw) override;

  /**
   * Turn the robot clockwise (using open-loop control). Uses velocity mode.
   *
   * @param ispeed motor power
   */
  void rotate(double ispeed) override;

  /**
   * Stop the robot (set all the motors to 0). Uses velocity mode.
   */
  void stop() override;

  /**
   * Drive the robot with a tank drive layout. Uses voltage mode.
   *
   * @param ileftSpeed left side speed
   * @param irightSpeed right side speed
   * @param ithreshold deadband on joystick values
   */
  void tank(double ileftSpeed, double irightSpeed, double ithreshold = 0) override;

  /**
   * Drive the robot with an arcade drive layout. Uses voltage mode.
   *
   * @param iforwardSpeed speed in the forward direction
   * @param iyaw speed around the vertical axis
   * @param ithreshold deadband on joystick values
   */
  void arcade(double iforwardSpeed, double iyaw, double ithreshold = 0) override;

  /**
   * Power the left side motors. Uses velocity mode.
   *
   * @param ispeed motor power
   */
  void left(double ispeed) override;

  /**
   * Power the right side motors. Uses velocity mode.
   *
   * @param ispeed motor power
   */
  void right(double ispeed) override;

  /**
   * Read the sensors.
   *
   * @return sensor readings in the format {left, right}
   */
  std::valarray<std::int32_t> getSensorVals() const override;

  /**
   * Reset the sensors to their zero point.
   */
  void resetSensors() override;

  /**
   * Set the brake mode for each motor.
   *
   * @param mode new brake mode
   */
  void setBrakeMode(AbstractMotor::brakeMode mode) override;

  /**
   * Set the encoder units for each motor.
   *
   * @param units new motor encoder units
   */
  void setEncoderUnits(AbstractMotor::encoderUnits units) override;

  /**
   * Set the gearset for each motor.
   *
   * @param gearset new motor gearset
   */
  void setGearing(AbstractMotor::gearset gearset) override;

  /**
   * Sets new PID constants.
   *
   * @param ikF the feed-forward constant
   * @param ikP the proportional constant
   * @param ikI the integral constant
   * @param ikD the derivative constant
   * @return 1 if the operation was successful or PROS_ERR if the operation failed, setting errno.
   */
  void setPosPID(double ikF, double ikP, double ikI, double ikD) override;

  /**
   * Sets new PID constants.
   *
   * @param ikF the feed-forward constant
   * @param ikP the proportional constant
   * @param ikI the integral constant
   * @param ikD the derivative constant
   * @param ifilter a constant used for filtering the profile acceleration
   * @param ilimit the integral limit
   * @param ithreshold the threshold for determining if a position movement has reached its goal
   * @param iloopSpeed the rate at which the PID computation is run (in ms)
   * @return 1 if the operation was successful or PROS_ERR if the operation failed, setting errno.
   */
  void setPosPIDFull(double ikF,
                     double ikP,
                     double ikI,
                     double ikD,
                     double ifilter,
                     double ilimit,
                     double ithreshold,
                     double iloopSpeed) override;

  /**
   * Sets new PID constants.
   *
   * @param ikF the feed-forward constant
   * @param ikP the proportional constant
   * @param ikI the integral constant
   * @param ikD the derivative constant
   * @return 1 if the operation was successful or PROS_ERR if the operation failed, setting errno.
   */
  void setVelPID(double ikF, double ikP, double ikI, double ikD) override;

  /**
   * Sets new PID constants.
   *
   * @param ikF the feed-forward constant
   * @param ikP the proportional constant
   * @param ikI the integral constant
   * @param ikD the derivative constant
   * @param ifilter a constant used for filtering the profile acceleration
   * @param ilimit the integral limit
   * @param ithreshold the threshold for determining if a position movement has reached its goal
   * @param iloopSpeed the rate at which the PID computation is run (in ms)
   * @return 1 if the operation was successful or PROS_ERR if the operation failed, setting errno.
   */
  void setVelPIDFull(double ikF,
                     double ikP,
                     double ikI,
                     double ikD,
                     double ifilter,
                     double ilimit,
                     double ithreshold,
                     double iloopSpeed) override;

  /**
   * Sets a new maximum velocity in RPM [0-600].
   *
   * @param imaxVelocity the new maximum velocity
   */
  void setMaxVelocity(double imaxVelocity) override;

  /**
   * Returns the maximum velocity in RPM [0-600].
   *
   * @return The maximum velocity in RPM [0-600].
   */
  double getMaxVelocity() const override;

  /**
   * Sets a new maximum voltage in mV [0-12000].
   *
   * @param imaxVoltage the new maximum voltage
   */
  void setMaxVoltage(double imaxVoltage) override;

  /**
   * Returns the maximum voltage in mV [0-12000].
   *
   * @return The maximum voltage in mV [0-12000].
   */
  double getMaxVoltage() const override;

  /**
   * Returns the left side motor.
   *
   * @return the left side motor
   */
  std::shared_ptr<AbstractMotor> getLeftSideMotor() const;

  /**
   * Returns the left side motor.
   *
   * @return the left side motor
   */
  std::shared_ptr<AbstractMotor> getRightSideMotor() const;

  protected:
  double maxVelocity;
  double maxVoltage;
  std::shared_ptr<AbstractMotor> leftSideMotor;
  std::shared_ptr<AbstractMotor> rightSideMotor;
  std::shared_ptr<ContinuousRotarySensor> leftSensor;
  std::shared_ptr<ContinuousRotarySensor> rightSensor;
};
} // namespace okapi
