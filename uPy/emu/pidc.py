# emulib – PID Controller


EPSILON = 1e-10  # smallest time resolution for which calculations are still numerical stable


class PIDController:
    def __init__(self, gains = [0, 0, 0], limits = [-1e9, 1e9, -1e9, 1e9]):
        self.gainP = gains[0]
        self.gainI = gains[1]
        self.gainD = gains[2]
        self.tau = 0.0
        self.reset()
        self.setIntegralLimits(limits[0], limits[1])
        self.setOutputLimits(limits[2], limits[3])

    def reset(self):
        self.errDerivativeLast = 0.0
        self.errIntegral = 0.0
        self.errLast = 0.0

    def setIntegralLimits(self, limitmin, limitmax):
        self.errIntegralMin = limitmin
        self.errIntegralMax = limitmax

    def setOutputLimits(self, limitmin, limitmax):
        self.errOutputMin = limitmin
        self.errOutputMax = limitmax

    def _derivative(self, error, dt):
        if dt < EPSILON: return 0.0
        errDerivative = (error - self.errLast) / dt

        # apply discrete low pass filter if tau is set
        if self.tau != 0.0:
            errDerivative = self.errDerivativeLast + (dt / (self.tau + dt)) * (errDerivative - self.errDerivativeLast)

        self.errDerivativeLast = errDerivative
        return errDerivative


    def _saturate(x, limitmin, limitmax):
        return min(max(x, limitmin), limitmax)

    def _integral(self, error, dt):
        errI = self.errIntegral + error * dt
        errI = min(max(errI, self.errIntegralMin), self.errIntegralMax)
        self.errIntegral = errI
        return errI


    def step(self, error, dt):
        errI = self._integral(error, dt)
        errD = self._derivative(error, dt)
        self.errLast = error

        # the simple beauty of PID
        output = error * self.gainP + \
                 errI  * self.gainI + \
                 errD  * self.gainD

        output = min(max(output, self.errIntegralMin), self.errIntegralMax)
        # print("PID: err={:.2f}, I={:.2f}, D={:.2f}, out={:.2f}".format(error, errI, errD, output)) # DBGME

        return output

    def __repr__(self):
        return "PID with P={:.2e}, I={:.2e}, D={:.2e}".format(self.gainP, self.gainI, self.gainD)
