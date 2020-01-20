import Sequelize from 'sequelize';

import databaseConfig from '../config/database';
import Sensor from '../app/models/Sensor';
import Measurement from '../app/models/Measurement';

const models = [Sensor, Measurement];

class Database {
  constructor() {
    this.connection = new Sequelize(databaseConfig);

    this.init();
    this.associate();
  }

  init() {
    models.forEach(model => model.init(this.connection));
  }

  associate() {
    models.forEach(model => {
      if (model.associate) {
        model.associate(this.connection.models);
      }
    });
  }
}

export default new Database();
