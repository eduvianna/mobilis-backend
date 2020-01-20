import { Router } from 'express';

import MeasurementController from './app/controllers/MeasurementController';
import SensorController from './app/controllers/SensorController';

const routes = new Router();

routes.post('/create-sensor', SensorController.store);
routes.put('/update-sensor', SensorController.update);

routes.post('/create-measurement', MeasurementController.store);

export default routes;
